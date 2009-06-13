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
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include "battle.hpp"

#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "hero.hpp"
#include "timer.hpp"

//events_engine
using events_engine::input;
using events_engine::keys;
using events_engine::mouse;
using events_engine::BUTTON;
using events_engine::NORMAL;
using events_engine::ATTACK;
using events_engine::MOVE;
using events_engine::ILLEGAL;
using events_engine::WAIT;
// video_engine
using video_engine::screen;
using video_engine::RANDOM;

// Constructor
Battle::Battle(Hero &player, Unit **enemies, int num_enemies, const int terrain) : Map(20, 11) {
  // Set the hero
  this->player = &player;

  // Set the enemies
  if (num_enemies > MAX_TEAM_UNITS) num_enemies = MAX_TEAM_UNITS;
  for (int i=0; i<num_enemies; i++)
    enemy_creatures[i] = enemies[i];
  for (int j=num_enemies; j<MAX_TEAM_UNITS; j++)
    enemy_creatures[j] = NULL;
  // Put the enemy creatures in the map.
  for (int i=0; i<num_enemies; i++) {
    enemy_creatures[i]->setFacingSide(LEFT);
    map[map_width-3][i+1].setCreature(enemy_creatures[i]);
  }

  // No enemy hero
  enemy = NULL;

  init(terrain);
}

// Constructor
Battle::Battle(Hero &player, Hero &enemy, const int terrain) : Map(20, 11) {
  // Set the hero
  this->player = &player;

  // Set the enemy
  this->enemy = &enemy;

  // Put the enemy hero and his units in the map.
  enemy.setFacingSide(LEFT);
  map[map_width-2][4].setCreature(&enemy);
  for (int i=0; i<MAX_TEAM_UNITS; i++) {
    if (enemy.getCreature(i))
      enemy.getCreature(i)->setFacingSide(LEFT);
    map[map_width-3][i+1].setCreature(enemy.getCreature(i));
  }

  // No enemy creatures
  for (int i = 0; i<MAX_TEAM_UNITS; i++)
    enemy_creatures[i] = NULL;

  init(terrain);
}

// Starts the battle.
void Battle::start(void) {
  draw();
  screen->transitionEffect(RANDOM);
  Map::start();
}

// Return_progress true if the battle was won.
bool Battle::win(void) {
  if (player) return true;
  else return false;
}

// Things to do no matter what constructor was called.
void Battle::init(const int terrain) {
  end_battle = false;

  makeMapVisible();

  // Put the hero and his units in the map.
  player->setFacingSide(RIGHT);
  map[1][4].setCreature(player);
  for (int i=0; i<MAX_TEAM_UNITS; i++) {
    if (player->getCreature(i))
      player->getCreature(i)->setFacingSide(RIGHT);
    map[2][i+1].setCreature(player->getCreature(i));
  }

  // Put all units' progress to 0
  for (int t=0; t<MAX_BATTLE_UNITS; t++) turn_progress[t] = 0;

  setTerrain(terrain, NULL);
}

// Controls the units not controled by the player.
void Battle::ai(void) {
  Cell *temp = getAttackCell();

  if (temp) { // Attack a unit
    moveSelectedCreature(*temp);
    selected_unit->attackCreature( *temp->getCreature() );
    animation(selected_unit->getNumSprites(ATTACKING)); // The attacking animation
    if ( temp->getCreature()->getNumber() == 0 ) {
      // Start the dying animation
      temp->getCreature()->setAnimation(DYING);
      animation(temp->getCreature()->getNumSprites(DYING));
      // delete the creature
      deleteCreature( *temp->getCreature() );
      temp->setCreature(NULL);
    }
    nextTurn();
  } else { // Move the unit
    int x, y;
    selected_unit->getPosition()->getCoordinates(x, y);
    x=0;
    while(!map[x][y].canMoveHere() && x<map_width-1) x++;
    if (x!=map_width-1) {
      moveSelectedCreature(map[x][y]);
      nextTurn();
    } else {
      selected_unit->getPosition()->unselect();
      nextTurn();
    }
  }
}

// Function to execute when the mouse is over a cell.
void Battle::mouseOverCell(const int x, const int y) {
  // Set the type of cursor needed
  if (selected_unit->getMaster() == enemy) {
    input->setCursorType(WAIT);
  } else if (map[x][y].getCreature()) {
    if (map[x][y].getCreature()->getMaster() != selected_unit->getMaster()) {
      if (map[x][y].canAttackHere() || selected_unit->getProjectiles())
        input->setCursorType(ATTACK);
      else
        input->setCursorType(ILLEGAL);
    } else {
      input->setCursorType(NORMAL);
    }
  } else if (map[x][y].canMoveHere()) {
    input->setCursorType(MOVE);
  } else {
    input->setCursorType(NORMAL);
  }
}

// Function to execute when the user left clicks on a cell.
void Battle::mouseLeftClick(const int x, const int y) {
  if ( selected_unit->getPosition() != &map[x][y] ) {
    if ( map[x][y].canMoveHere() ) {
      moveSelectedCreature(map[x][y]);
      nextTurn();
    } else if (map[x][y].getCreature() && selected_unit->getProjectiles()) { // Distant attack
      if ( map[x][y].getCreature()->getMaster() != selected_unit->getMaster() ) {
        selected_unit->getPosition()->unselect();
        selected_unit->attackCreature( *map[x][y].getCreature() );
        animation(selected_unit->getNumSprites(ATTACKING));
        // Check if the creatures is dead.
        if ( map[x][y].getCreature()->getNumber() == 0 ) {
          // Start the dying animation
          map[x][y].getCreature()->setAnimation(DYING);
          animation(map[x][y].getCreature()->getNumSprites(DYING));
          // delete the creature
          deleteCreature(*map[x][y].getCreature());
          map[x][y].setCreature(NULL);
        }
        nextTurn();
      }
    } else if ( map[x][y].canAttackHere() ) { // Close attack
      if ( map[x][y].getCreature()->getMaster() != selected_unit->getMaster() ) {
        moveSelectedCreature(map[x][y]);
        selected_unit->attackCreature( *map[x][y].getCreature() );
        //creature_animation_active = true;
        animation(selected_unit->getNumSprites(ATTACKING)); // The attacking animation
        // Check if the creatures is dead.
        if ( map[x][y].getCreature()->getNumber() == 0 ) {
          // Start the dying animation
          map[x][y].getCreature()->setAnimation(DYING);
          animation(map[x][y].getCreature()->getNumSprites(DYING));
          // delete the creature
          deleteCreature(*map[x][y].getCreature());
          map[x][y].setCreature(NULL);
        }
        nextTurn();
      }
    }
  }
}

// Starts the next turn.
void Battle::nextTurn(void) {
  // Check if the battle has ended

  // Check if the hero is dead
  if (player == NULL) end_battle = true;
  // Calculate number of dead creatures
  int counter = 0;
  for (int i = 0; i<MAX_TEAM_UNITS; i++)
    if (enemy_creatures[i] == NULL) counter++;
  // Check if there are no enemies
  if (counter == MAX_TEAM_UNITS && !enemy) end_battle = true;

  // If the battle hasn't ended continue
  if (!end_battle) {
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
  while (mouse[BUTTON]) input->readInput();
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

// Function to call whenever there is an animation.
void Battle::animation(const int sprites) {
  /// @todo Use the loop function in game_loop.hpp
  int frame = 0;
  Timer fps;

  while (frame/NUM_FRAMES_FOR_SPRITE < sprites) {
    fps.start();
    input->readInput();
    draw();
    screen->update();
    fps.end(30);
    frame++;
  }
}

// This function is executed in the main loop. If
// it return_progress true, the loop ends, else it continues.
bool Battle::frame(void) {
  adjustVisibleMap();
  if (keys[SDLK_ESCAPE]) {
    keys[SDLK_ESCAPE] = false;
    deleteCreature(*player);
    end_battle = true;
  } else if (!end_battle) { // If the battle wasn't ended continue.
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
    draw();
  }

  return end_battle;
}

// Creates and starts the default battle.
void createDefaultBattle(void) {
  Hero *player;
  Unit *creature[9];
  Unit *temp;

  // Create the hero and it's units.
  player = new Hero(ELF);
  for (int j=0; j<9; j++) {
    temp = new Unit(SHYDE, 5);
    player->recruitCreature(temp);
  }
  // Create the enemy creatures.
  /// @todo Free this units.
  for (int i=0; i<5; i++) {
    creature[i] = new Unit(SKELETON, 3);
  }
  for (int t=5; t<9; t++) {
    creature[t] = new Unit(BAT, 10);
  }

  Battle war(*player, creature, 9, FLAT_GRASS);
  war.start();

  if (war.win())
    delete player;

  // Make sure the cursors's state is normal
  input->setCursorType(NORMAL);
}

// Creates and starts a battle.
bool createBattle(Hero &player, const char enemy_type, const char terrain_type) {
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
  input->setCursorType(NORMAL);

  return war.win();
}

// Creates and starts a battle.
bool createBattle(Hero &player, Hero &enemy, const char terrain_type) {
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
  input->setCursorType(NORMAL);

  return war.win();
}
