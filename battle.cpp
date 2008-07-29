/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007-2008  Jon Ander Peñalba <jonan88@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include "battle.hpp"

#include <cstdlib>

#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "hero.hpp"
#include "timer.hpp"
#include "unit.hpp"

//events_engine
using events_engine::input;
using events_engine::keys;
using events_engine::mouse;

using events_engine::POSITION_X;
using events_engine::POSITION_Y;
using events_engine::BUTTON;

// video_engine
using video_engine::screen;

using video_engine::RIGHT;
using video_engine::LEFT;

using video_engine::RANDOM;

// Constructor
Battle::Battle(Hero &player, Unit **enemies, const int num_enemies) : Map(18, 9) {
  // Set the hero
  this->player = &player;
  // Set the enemies
  for (int i=0; i<num_enemies && i<MAX_TEAM_UNITS; i++)
    creatures[i] = enemies[i];
  if (num_enemies<MAX_TEAM_UNITS)
    for (int j=num_enemies; j<MAX_TEAM_UNITS; j++)
      creatures[j] = NULL;
  // Put turns to 0
  for (int t=0; t<MAX_BATTLE_UNITS; t++) turns[t] = 0;

  end_battle = false;

  // Make the hole map visible
  for (int x=0; x<18; x++)
    for (int y=0; y<9; y++)
      battle_map[x][y].calculateView(1);
  // Put the hero and his units in the map.
  player.setFacingSide(RIGHT);
  battle_map[0][4].setCreature(&player);
  for (int i=0; i<9; i++) {
    player.getCreature(i)->setFacingSide(RIGHT);
    battle_map[1][i].setCreature(player.getCreature(i));
  }
  // Put the enemy creatures in the map.
  for (int i=0; i<MAX_TEAM_UNITS; i++) {
    creatures[i]->setFacingSide(LEFT);
    battle_map[width-2][i].setCreature(creatures[i]);
  }
}

// Starts the battle.
void Battle::start(void) {
  draw();
  screen->transitionEffect(RANDOM);
  Map::start();
}

// Returns true if the battle was won.
bool Battle::win(void) {
  if (player) return true;
  else return false;
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool Battle::frame(void) {
  if (keys[SDLK_ESCAPE]) {
    keys[SDLK_ESCAPE] = false;
    deleteCreature(*player);
    end_battle = true;
  } else if (!end_battle) { // If the battle wasn't ended continue.
    if (selected_unit->getMaster() == NULL) ai();
    else {
      // This controls only work when a friendly creature is moving
      if (keys[SDLK_SPACE]) {
        keys[SDLK_SPACE] = false;
        selected_unit->getPosition()->unselect(selected_unit->getMovement());
        nextTurn();
      }
      moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
    }
    draw();
  }

  return end_battle;
}

// Function to execute when the user clicks on a cell.
void Battle::mouseClick(const int x, const int y) {
  if ( selected_unit->getPosition() != &battle_map[x][y] ) {
    if ( battle_map[x][y].canMoveHere() ) {
      moveCreature(battle_map[x][y]);
      nextTurn();
    } else if ( battle_map[x][y].canAttackHere() ) {
      if ( battle_map[x][y].getCreature()->getMaster() != selected_unit->getMaster() ) {
        moveCreature(battle_map[x][y]);
        selected_unit->attackCreature( *battle_map[x][y].getCreature() );
        animation(selected_unit->getNumSprites(ATTACKING)); // The attacking animation
        // Check if the creatures is dead.
        if ( battle_map[x][y].getCreature()->getNumber() == 0 ) {
          // Start the dying animation
          battle_map[x][y].getCreature()->startAnimation(DYING);
          animation(battle_map[x][y].getCreature()->getNumSprites(DYING));
          // delete the creature
          deleteCreature(*battle_map[x][y].getCreature());
          battle_map[x][y].setCreature(NULL);
        }
        nextTurn();
      }
    }
  }
}

// Starts the next turn.
void Battle::nextTurn(void) {
  bool done = false;
  Unit* creature;

  // Check if the battle has ended
  // Check if the hero is dead
  if (player == NULL) end_battle = true;
  // Check if all enemy creatures are dead
  int counter = 0;
  for (int i = 0; i<MAX_TEAM_UNITS; i++)
    if (creatures[i] == NULL) counter++;
  if (counter == MAX_TEAM_UNITS) end_battle = true;
  // If the battle hasn't ended continue
  if (!end_battle) {
    // Search for the next creature
    while (!done) {
      // Look if it's someones turn
      for (int i=0; i<MAX_BATTLE_UNITS && !done; i++)
        if (turns[i]>=TURN) {
          turns[i] -= TURN;
          if (i==0) {
            if (player) {
              done = true;
              turn = 0;
              creature = player;
            }
          } else if (i<MAX_TEAM_UNITS+1) {
            if (player->getCreature(i-1)) {
              done = true;
              turn = i;
              creature = player->getCreature(i-1);
            }
          } else if ( i<(2*MAX_TEAM_UNITS+1) ) {
            if (creatures[i-MAX_TEAM_UNITS-1]) {
              done = true;
              turn = i;
              creature = creatures[i-MAX_TEAM_UNITS-1];
            }
          }

        }
      // Increase all the turns
      for (int j=0; j<MAX_BATTLE_UNITS && !done; j++) {
        if (j==0) {
          if (player)
            turns[j] += player->getAgility();
        } else if (j<MAX_TEAM_UNITS+1) {
          if (player->getCreature(j-1))
            turns[j] += player->getCreature(j-1)->getAgility();
        } else if ( j<(2*MAX_TEAM_UNITS+1) ) {
          if (creatures[j-MAX_TEAM_UNITS-1])
          turns[j] += creatures[j-MAX_TEAM_UNITS-1]->getAgility();
        }
      }
    }
    selected_unit = creature;
    selected_unit->getPosition()->select();
    // Wait until the mouse button is released.
    while (mouse[BUTTON]) input->readInput();
  }
}

// Deletes a creature.
void Battle::deleteCreature(Unit &creature) {
  bool found = false;
  int i = 0;

  while (i<MAX_BATTLE_UNITS && !found) {
    if (i==0) {
      if (player == &creature) {
        player = NULL;
        found = true;
      }
    } else if (i<MAX_TEAM_UNITS+1) {
      if (player->getCreature(i-1) == &creature) {
        /// @todo Do the same without recruitCreature(unit*, int)
        player->recruitCreature(NULL, i-1);
        found = true;
      }
    } else if (i<(2*MAX_TEAM_UNITS+1)) {
      if (creatures[i-MAX_TEAM_UNITS-1] == &creature) {
        creatures[i-MAX_TEAM_UNITS-1] = NULL;
        found = true;
      }
    }
    i++;
  }
  delete &creature;
}

// Controls the units not controled by the player.
void Battle::ai(void) {
  Cell *temp;
  temp = getAttackCell();

  if (temp) { // Attack a unit
    moveCreature(*temp);
    selected_unit->attackCreature( *temp->getCreature() );
    animation(selected_unit->getNumSprites(ATTACKING)); // The attacking animation
    if ( temp->getCreature()->getNumber() == 0 ) {
      // Start the dying animation
      temp->getCreature()->startAnimation(DYING);
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
    while(!battle_map[x][y].canMoveHere() && x<width) x++;
    if (x!=width) {
      moveCreature(battle_map[x][y]);
      nextTurn();
    } else {
      selected_unit->getPosition()->unselect(selected_unit->getMovement());
      nextTurn();
    }
  }
}

// Function to call whenever there is an animation.
void Battle::animation(const int sprites) {
  /// @todo Use the loop function in loop.hpp
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

// Creates and starts a battle.
void createDefaultBattle(void) {
  Hero *player;
  Unit *creature[9];
  Unit *temp;

  // Create the hero and it's units.
  player = new Hero(FIGHTER, HUMAN);
  for (int j=0; j<9; j++) {
    temp = new Unit(SERGEANT, 3);
    player->recruitCreature(temp);
  }
  // Create the enemy creatures.
  for (int i=0; i<5; i++) {
    creature[i] = new Unit(SKELETON, 5);
  }
  for (int t=5; t<9; t++) {
    creature[t] = new Unit(BAT, 1);
  }

  Battle war(*player, creature, 9);
  war.setTerrain(FLAT_GRASS, -1, -1);
  war.start();

  /// @todo Free memory
  // Free memory
  /*if (player) delete player;
  for (int i=0; i<9; i++) {
    if (creature[i]) delete creature[i];
  }*/
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
    creature[i] = new Unit(enemy_type, num_enemies);
  }

  Battle war(player, creature, 9);
  war.setTerrain(terrain_type, -1, -1);
  war.start();

  // Restore player's position
  if (war.win()) temp->setCreature(&player);

  return war.win();
}
