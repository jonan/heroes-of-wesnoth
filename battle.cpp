/*
This file is part of Heroes of Wesnoth.
Copyright (C) 2007, 2008, 2009 Jon Ander Peñalba <jonan88@gmail.com>

Heroes of Wesnoth is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

Heroes of Wesnoth is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Heroes of Wesnoth. If not, see <http://www.gnu.org/licenses/>
*/

#include "battle.hpp"

#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "hero.hpp"
#include "unit_animation.hpp"

//events_engine
using events_engine::input;
using events_engine::keys;
using events_engine::mouse;
using events_engine::MOUSE_BUTTON;
using events_engine::ATTACK_CURSOR;
using events_engine::ILLEGAL_CURSOR;
using events_engine::MOVE_CURSOR;
using events_engine::NORMAL_CURSOR;
using events_engine::WAIT_CURSOR;
// video_engine
using video_engine::screen;
using video_engine::RANDOM_EFFECT;
using video_engine::FACE_LEFT;
using video_engine::FACE_RIGHT;

// Constructor
Battle::Battle(Hero &player, Unit **enemies, int num_enemies, const char *terrain) : Map(20, 11) {
  // Set the enemies
  for (int i=0; i<num_enemies; i++)
    creatures[ENEMY+1+i] = enemies[i];
  for (int j=num_enemies; j<MAX_TEAM_UNITS; j++)
    creatures[ENEMY+1+j] = NULL;
  // Put the enemy creatures in the map.
  for (int i=0; i<num_enemies; i++) {
    creatures[ENEMY+1+i]->setFacingSide(FACE_LEFT);
    map[map_width-3][i+1].setCreature(creatures[ENEMY+1+i]);
  }

  // No enemy hero
  creatures[ENEMY] = NULL;

  init(player, terrain);
}

// Constructor
Battle::Battle(Hero &player, Hero &enemy, const char *terrain) : Map(20, 11) {
  setHero(enemy, FACE_LEFT);
  init(player, terrain);
}

// Starts the battle.
void Battle::start(void) {
  draw();
  screen->transitionEffect(RANDOM_EFFECT);
  Map::start();
}

// Things to do no matter what constructor was called.
void Battle::init(Hero &player_hero, const char *terrain) {
  setHero(player_hero, FACE_RIGHT);
  makeMapVisible();

  // Put all units' progress to 0
  for (int t=0; t<MAX_BATTLE_UNITS; t++)
    turn_progress[t] = 0;

  setTerrainToAllCells(terrain);
}

// Put a hero and his units in the map.
void Battle::setHero(Hero &hero, const int facing_side) {
  int hero_pos_x;
  int creatures_pos_x;
  int side;

  if (facing_side == FACE_RIGHT) {
    side = PLAYER;
    hero_pos_x = 1;
    creatures_pos_x = 2;
  } else {
    side = ENEMY;
    hero_pos_x = map_width-2;
    creatures_pos_x = map_width-3;
  }

  // Set hero
  creatures[side] = &hero;
  hero.setFacingSide(facing_side);
  map[hero_pos_x][4].setCreature(&hero);
  // Set units
  for (int i=0; i<MAX_TEAM_UNITS; i++) {
    creatures[side+1+i] = hero.getCreature(i);
    if (creatures[side+1+i]) {
      creatures[side+1+i]->setFacingSide(facing_side);
      map[creatures_pos_x][i+1].setCreature(creatures[side+1+i]);
    }
  }
}

// Controls the units not controled by the player.
void Battle::ai(void) {
  Cell *temp = getAttackCell();

  if (temp) { // Attack a unit
    attack(*temp);
  } else { // Move the unit
    int x, y;
    selected_unit->getPosition()->getCoordinates(x, y);
    x=0;
    while(!map[x][y].canMoveHere() && x<map_width-1)
      x++;
    if (x!=map_width-1)
      move(map[x][y]);
    else
      selected_unit->getPosition()->unselect();
  }
}

// Makes the selected creature attack the unit in the given cell.
void Battle::attack(Cell &cell) {
  animation->startNewAnimation(ATTACK, *selected_unit, &cell);
}

// Function to execute when the mouse is over a cell.
void Battle::mouseOverCell(const int x, const int y) {
  // Set the type of cursor needed
  if (map[x][y].getCreature()) {
    if (map[x][y].getCreature()->getMaster() != selected_unit->getMaster()) {
      if (map[x][y].canAttackHere() || selected_unit->getProjectiles())
        input->setCursorType(ATTACK_CURSOR);
      else
        input->setCursorType(ILLEGAL_CURSOR);
    } else {
      input->setCursorType(NORMAL_CURSOR);
    }
  } else if (map[x][y].canMoveHere()) {
    input->setCursorType(MOVE_CURSOR);
  } else {
    input->setCursorType(NORMAL_CURSOR);
  }
}

// Function to execute when the user left clicks on a cell.
void Battle::mouseLeftClick(const int x, const int y) {
  if ( selected_unit->getPosition() != &map[x][y] ) {
    if (map[x][y].getCreature()) {
      if (map[x][y].getCreature()->getMaster() != selected_unit->getMaster() ) {
        // Check close attack
        bool can_attack = map[x][y].canAttackHere();
        // Check distant attack
        can_attack |= map[x][y].getCreature() && selected_unit->getProjectiles();
        if (can_attack)
          attack(map[x][y]);
      }
    } else if ( map[x][y].canMoveHere() ) {
      move(map[x][y]);
    }
  }
}

// Starts the next turn.
void Battle::nextTurn(void) {
  // Check if the battle has ended
  // Check if the hero is dead
  if (creatures[PLAYER] == NULL)
    end_map = true;
  // Calculate number of dead creatures
  int counter = 0;
  for (int i=0; i<MAX_TEAM_UNITS; i++) {
    if (creatures[ENEMY+1+i] == NULL)
      counter++;
  }
  // Check if there are no enemies
  if (counter == MAX_TEAM_UNITS && !creatures[ENEMY])
    end_map = true;

  // If the battle hasn't ended continue
  if (!end_map) {
    bool done = false;
    int turn;
    // Search for the next creature
    while (!done) {
      // Look if it's someones turn
      for (int i=0; i<MAX_BATTLE_UNITS && !done; i++) {
        if (turn_progress[i] >= TURN) {
          turn_progress[i] -= TURN;
          if (creatures[i]) {
            done = true;
            turn = i;
          }
        }
      }
      // If it's no one's turn, increase all the turn_progress
      for (int j=0; j<MAX_BATTLE_UNITS && !done; j++) {
        if (creatures[j])
          turn_progress[j] += creatures[j]->getAgility();
      }
    }
    selected_unit = creatures[turn];
    selected_unit->getPosition()->select();
  }
  // If the mouse button is pressed wait until it's released.
  while (mouse[MOUSE_BUTTON]) input->readInput();
}

// Deletes a creature.
void Battle::deleteCreature(Unit &creature) {
  if (&creature == creatures[PLAYER] || &creature == creatures[ENEMY]) {
    Hero *hero = static_cast<Hero*>(&creature);
    // Remove the hero's units from the battle
    for (int j=0; j<MAX_TEAM_UNITS; j++) {
      if (hero->getCreature(j))
        hero->getCreature(j)->getPosition()->setCreature(NULL);
    }
    delete &creature;
    if (&creature == creatures[PLAYER]) {
      creatures[PLAYER] = NULL;
    } else {
      creatures[ENEMY] = NULL;
    }
  } else {
    bool found = false;
    for (int i=0; i<MAX_TEAM_UNITS && !found; i++) {
      if (creatures[PLAYER+1+i] == &creature) {
        /// @todo Do the same without recruitCreature(unit*, int)
        static_cast<Hero*>(creatures[PLAYER])->recruitCreature(NULL, i);
        creatures[PLAYER+1+i] = NULL;
        found = true;
      } else if (creatures[ENEMY+1+i] == &creature) {
        if (creatures[ENEMY]) {
          /// @todo Do the same without recruitCreature(unit*, int)
          static_cast<Hero*>(creatures[ENEMY])->recruitCreature(NULL, i);
        }
        creatures[ENEMY+1+i] = NULL;
        found = true;
      }
    }
    delete &creature;
  }
}

// This function is executed in the main loop. If
// it return_progress true, the loop ends, else it continues.
bool Battle::frame(void) {
  if (Map::frame()) {
    deleteCreature(*creatures[PLAYER]);
  } else { // If the battle wasn't ended continue.
    // Check if there's an animation in progress
    if (animation->animationInProgress()) {
      if (animation->frame()) {
        if (animation->getType() == ATTACK) {
          Unit *enemy_creature = animation->getFinalPosition()->getCreature();
          selected_unit->damageCreature(*enemy_creature);
          if ( enemy_creature->getNumber() == 0 )
            animation->startNewAnimation(DIE, *enemy_creature);
          else
            nextTurn();
        } else if (animation->getType() == DIE) {
          animation->getUnit()->getPosition()->setCreature(NULL);
          deleteCreature(*animation->getUnit());
          nextTurn();
        } else if (animation->getType() == MOVE) {
          nextTurn();
        }
      }
    } else {
      // If there's no animation do normal stuff
      if (selected_unit->getMaster() == creatures[ENEMY]) {
        ai();
      } else {
        // This controls only work when a friendly creature is moving
        if (keys[SDLK_SPACE]) {
          keys[SDLK_SPACE] = false;
          selected_unit->getPosition()->unselect();
          nextTurn();
        }
        updateMouse();
      }
    }
    // Draw the map
    adjustVisibleMap();
    draw();
  }

  return end_map;
}

// Creates and starts the default battle.
void createDefaultBattle(void) {
  Hero *player;
  Unit *creature[9];
  Unit *temp;

  // Create the hero and it's units.
  player = new Hero("elf");
  for (int j=0; j<9; j++) {
    temp = new Unit("shyde", 5);
    player->recruitCreature(temp);
  }
  // Create the enemy creatures.
  /// @todo Free this units.
  for (int i=0; i<5; i++) {
    creature[i] = new Unit("skeleton", 3);
  }
  for (int t=5; t<9; t++) {
    creature[t] = new Unit("bat", 10);
  }

  Battle war(*player, creature, 9, "flat_grass");
  war.start();

  if (war.win())
    delete player;

  // Make sure the cursors's state is normal
  input->setCursorType(NORMAL_CURSOR);
}

// Creates and starts a battle.
bool createBattle(Hero &player, const char *enemy_type, const char *terrain_type) {
  Cell *temp;
  Unit *creature[9];
  int num_enemies;

  // Save players position in the world
  temp = player.getPosition();

  // Create the enemy creatures.
  num_enemies = rand() % 5;
  num_enemies++;
  for (int i=0; i<9; i++) {
    // Enemy creatures aren't deleted because in the future we will need them
    creature[i] = new Unit(enemy_type, num_enemies);
  }

  Battle war(player, creature, 9, terrain_type);
  war.start();

  // Restore player's position
  if (war.win())
    temp->setCreature(&player);
  else
    temp->setCreature(NULL);

  // Make sure the cursors's state is normal
  input->setCursorType(NORMAL_CURSOR);

  return war.win();
}

// Creates and starts a battle.
bool createBattle(Hero &player, Hero &enemy, const char *terrain_type) {
  Cell *temp[2];

  // Save heroes positions in the world
  temp[0] = player.getPosition();
  temp[1] = enemy.getPosition();

  Battle war(player, enemy, terrain_type);
  war.start();

  // Restore winner's position
  if (war.win()) {
    temp[0]->setCreature(&player);
    temp[1]->setCreature(NULL);
  } else {
    temp[0]->setCreature(NULL);
    temp[1]->setCreature(&enemy);
  }

  // Make sure the cursors's state is normal
  input->setCursorType(NORMAL_CURSOR);

  return war.win();
}
