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
    enemy_creatures[i] = enemies[i];
  for (int j=num_enemies; j<MAX_TEAM_UNITS; j++)
    enemy_creatures[j] = NULL;
  // Put the enemy creatures in the map.
  for (int i=0; i<num_enemies; i++) {
    enemy_creatures[i]->setFacingSide(FACE_LEFT);
    map[map_width-3][i+1].setCreature(enemy_creatures[i]);
  }

  // No enemy hero
  enemy = NULL;

  init(player, terrain);
}

// Constructor
Battle::Battle(Hero &player, Hero &enemy, const char *terrain) : Map(20, 11) {
  setHero(enemy, FACE_LEFT);

  // No enemy creatures
  for (int i = 0; i<MAX_TEAM_UNITS; i++)
    enemy_creatures[i] = NULL;

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
  for (int t=0; t<MAX_BATTLE_UNITS; t++) turn_progress[t] = 0;

  setTerrainToAllCells(terrain);
}

// Put a hero and his units in the map.
void Battle::setHero(Hero &hero, const int facing_side) {
  int hero_pos_x;
  int creatures_pos_x;

  if (facing_side == FACE_RIGHT) {
    player = &hero;
    hero_pos_x = 1;
    creatures_pos_x = 2;
  } else {
    enemy = &hero;
    hero_pos_x = map_width-2;
    creatures_pos_x = map_width-3;
  }

  hero.setFacingSide(facing_side);
  map[hero_pos_x][4].setCreature(&hero);
  for (int i=0; i<MAX_TEAM_UNITS; i++) {
    if (hero.getCreature(i))
      hero.getCreature(i)->setFacingSide(facing_side);
    map[creatures_pos_x][i+1].setCreature(hero.getCreature(i));
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
    if ( map[x][y].canMoveHere() ) {
      move(map[x][y]);
    } else if (map[x][y].getCreature() && selected_unit->getProjectiles()) { // Distant attack
      /**if ( map[x][y].getCreature()->getMaster() != selected_unit->getMaster() ) {
        selected_unit->getPosition()->unselect();
        selected_unit->attackCreature( *map[x][y].getCreature() );
        createAnimation(selected_unit->getNumSprites(ATTACKING));
        // Check if the creatures is dead.
        if ( map[x][y].getCreature()->getNumber() == 0 ) {
          // Start the dying animation
          map[x][y].getCreature()->setAnimation(DYING);
          createAnimation(map[x][y].getCreature()->getNumSprites(DYING));
          // delete the creature
          deleteCreature(*map[x][y].getCreature());
          map[x][y].setCreature(NULL);
        }
        nextTurn();
      }*/
    } else if ( map[x][y].canAttackHere() ) { // Close attack
      if ( map[x][y].getCreature()->getMaster() != selected_unit->getMaster() )
        attack(map[x][y]);
    }
  }
}

// Starts the next turn.
void Battle::nextTurn(void) {
  // Check if the battle has ended

  // Check if the hero is dead
  if (player == NULL) end_map = true;
  // Calculate number of dead creatures
  int counter = 0;
  for (int i = 0; i<MAX_TEAM_UNITS; i++)
    if (enemy_creatures[i] == NULL) counter++;
  // Check if there are no enemies
  if (counter == MAX_TEAM_UNITS && !enemy) end_map = true;

  // If the battle hasn't ended continue
  if (!end_map) {
    bool done = false;
    Unit* creature = NULL;
    // Search for the next creature
    while (!done) {
      // Look if it's someones turn
      for (int i=0; i<MAX_BATTLE_UNITS && !done; i++)
        if (turn_progress[i]>=TURN) {
          turn_progress[i] -= TURN;
          if (i==0) {
              done = true;
              turn = 0;
              creature = player;
          } else if (i<MAX_TEAM_UNITS+1) {
            if (player->getCreature(i-1)) {
              done = true;
              turn = i;
              creature = player->getCreature(i-1);
            }
          } else if (i==10) {
            if (enemy) {
              done = true;
              turn = 10;
              creature = enemy;
            }
          } else if ( i<MAX_BATTLE_UNITS ) {
            if (enemy) {
              if (enemy->getCreature(i-MAX_TEAM_UNITS-2)) {
                done = true;
                turn = i;
                creature = enemy->getCreature(i-MAX_TEAM_UNITS-2);
              }
            } else {
              if (enemy_creatures[i-MAX_TEAM_UNITS-2]) {
                done = true;
                turn = i;
                creature = enemy_creatures[i-MAX_TEAM_UNITS-2];
              }
            }
          }
        }
      // If it's no one's turn, increase all the turn_progress
      for (int j=0; j<MAX_BATTLE_UNITS && !done; j++) {
        if (j==0) {
          turn_progress[j] += player->getAgility();
        } else if (j<MAX_TEAM_UNITS+1) {
          if (player->getCreature(j-1))
            turn_progress[j] += player->getCreature(j-1)->getAgility();
        } else if (j==10) {
          if (enemy) {
            turn_progress[j] += enemy->getAgility();
          }
        } else if ( j<MAX_BATTLE_UNITS ) {
          if (enemy) {
            if (enemy->getCreature(j-MAX_TEAM_UNITS-2))
              turn_progress[j] += enemy->getCreature(j-MAX_TEAM_UNITS-2)->getAgility();
          } else {
            if (enemy_creatures[j-MAX_TEAM_UNITS-2])
              turn_progress[j] += enemy_creatures[j-MAX_TEAM_UNITS-2]->getAgility();
          }
        }
      }
    }
    selected_unit = creature;
    selected_unit->getPosition()->select();
  }
  // If the mouse button is pressed wait until it's released.
  while (mouse[MOUSE_BUTTON]) input->readInput();
}

// Deletes a creature.
void Battle::deleteCreature(Unit &creature) {
  bool found = false;

  for (int i=0; i<MAX_BATTLE_UNITS && !found; i++) {
    if (i==0) {
      if (player == &creature) {
        // Remove the hero's units from the battle
        for (int j=0; j<MAX_TEAM_UNITS; j++) {
          if (player->getCreature(j))
            player->getCreature(j)->getPosition()->setCreature(NULL);
        }
        player = NULL;
        found = true;
      }
    } else if (i<MAX_TEAM_UNITS+1) {
      if (player->getCreature(i-1) == &creature) {
        /// @todo Do the same without recruitCreature(unit*, int)
        player->recruitCreature(NULL, i-1);
        found = true;
      }
    } else if (i==10) {
      if (enemy == &creature) {
        // Remove the hero's units from the battle
        for (int j=0; j<MAX_TEAM_UNITS; j++) {
          if (enemy->getCreature(j))
            enemy->getCreature(j)->getPosition()->setCreature(NULL);
        }
        enemy = NULL;
        found = true;
      }
    } else { // i<MAX_BATTLE_UNITS
      if (enemy) {
        if (enemy->getCreature(i-MAX_TEAM_UNITS-2) == &creature) {
          /// @todo Do the same without recruitCreature(unit*, int)
          enemy->recruitCreature(NULL, i-MAX_TEAM_UNITS-2);
          found = true;
        }
      } else {
        if (enemy_creatures[i-MAX_TEAM_UNITS-2] == &creature) {
          enemy_creatures[i-MAX_TEAM_UNITS-2] = NULL;
          found = true;
        }
      }
    }
  }
  delete &creature;
}

// This function is executed in the main loop. If
// it return_progress true, the loop ends, else it continues.
bool Battle::frame(void) {
  if (Map::frame()) {
    deleteCreature(*player);
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
      if (selected_unit->getMaster() == enemy) {
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
