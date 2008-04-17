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
#include "events.hpp"
#include "graphics.hpp"
#include "timer.hpp"
#include "unit.hpp"

// Puts the enemy creatures in the map.
void battle::setCreatures(void) {
   for (int i=0; i<MAX_CREATURES; i++)
      battleMap[sizeX-2][i].setCreature(creatures[i]);
}

// Function to execute when the cell where the mouse is over is detected.
void battle::mouseOver(const int x, const int y, const int button) {
   if ( button == 1  &&  (selectedUnit->getPosition() != &battleMap[x][y]) ) {
      if ( battleMap[x][y].canMoveHere() ) {
         moveCreature(&battleMap[x][y]);
         finishTurn();
      } else if ( battleMap[x][y].canAttackHere() ) {
         if ( battleMap[x][y].getCreature()->getMaster() != selectedUnit->getMaster() ) {
            moveCreature(&battleMap[x][y]);
            selectedUnit->attack( *battleMap[x][y].getCreature() );
            selectedUnit->getPosition()->unselect();
            if ( battleMap[x][y].getCreature()->getNumber() == 0 ) {
               removeCreature(*battleMap[x][y].getCreature());
               battleMap[x][y].setCreature(NULL);
            }
            if ( selectedUnit->getNumber() == 0) {
               removeCreature(*battleMap[x][y].getCreature());
               selectedUnit->getPosition()->setCreature(NULL);
            }
            finishTurn();
         }
      }
   }
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool battle::frame(void) {
   if (keys[SDLK_ESCAPE]) endBattle = true;
   if (keys[SDLK_SPACE]) {
      while (keys[SDLK_SPACE]) input->readInput();
      selectedUnit->getPosition()->unselect();
      finishTurn();
   }
   if (selectedUnit->getMaster() == NULL)
      ai();
   else
      moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   draw();
   return endBattle;
}

// Returns the next unit.
unit* battle::nextTurn(void) {
   bool done = false;

   while (!done) {
      // Look if it's someones turn
      for (int i=0; i<MAX_BATTLE_UNITS; i++)
         if (turns[i]>=TURN) {
            turns[i] -= TURN;
            if (i==0) {
               if (player) {
                  done = true;
                  turn = 0;
                  return player;
               }
            } else if (i<MAX_CREATURES+1) {
               if (player->getCreature(i-1)) {
                  done = true;
                  turn = i;
                  return player->getCreature(i-1);
               }
            } else if ( i<(2*MAX_CREATURES+1) ) {
               if (creatures[i-MAX_CREATURES-1]) {
                  done = true;
                  turn = i;
                  return creatures[i-MAX_CREATURES-1];
               }
            }

         }
      // Increase all the turns
      for (int j=0; j<MAX_BATTLE_UNITS; j++) {
         if (j==0) {
            if (player)
               turns[j] += player->getAgility();
         } else if (j<MAX_CREATURES+1) {
            if (player->getCreature(j-1))
               turns[j] += player->getCreature(j-1)->getAgility();
         } else if ( j<(2*MAX_CREATURES+1) ) {
            if (creatures[j-MAX_CREATURES-1])
               turns[j] += creatures[j-MAX_CREATURES-1]->getAgility();
         }
      }
   }
}

// Function to call when a turn ends.
void battle::finishTurn(void) {
   // Check if the battle has ended
   // Check if the hero is dead
   if (player == NULL) endBattle = true;
   // Check if all enemy creatures are dead
   int counter = 0;
   for (int i = 0; i<MAX_CREATURES; i++)
      if (creatures[i] == NULL) counter++;
   if (counter == MAX_CREATURES) endBattle = true;
   // If the battle hasn't ended continue
   if (!endBattle) {
      selectedUnit = nextTurn();
      selectedUnit->getPosition()->select();
      // Wait until the mouse button is released.
      while (mouse[BUTTON]) input->readInput();
   }
}

// Moves the selected creature to a given cell.
void battle::moveCreature(cell *endPosition) {
   int *path;
   int movements;
   cell *position = selectedUnit->getPosition();

   endPosition->getPath(path, movements);
   moveUnit(*selectedUnit, path, movements);
   position->unselect(selectedUnit->getMovement());
}

// Removes a unit from the battle.
void battle::removeCreature(unit &creature) {
   bool found = false;
   int i = 0;

   while (i<MAX_BATTLE_UNITS && !found) {
      if (i==0) {
         if (player == &creature) {
            player = NULL;
            found = true;
         }
      } else if (i<MAX_CREATURES+1) {
         if (player->getCreature(i-1) == &creature) {
            player->recruitCreature(NULL, i-1);
            found = true;
         }
      } else if (i<(2*MAX_CREATURES+1)) {
         if (creatures[i-MAX_CREATURES-1] == &creature) {
            creatures[i-MAX_CREATURES-1] = NULL;
            found = true;
         }
      }
      i++;
   }
   delete &creature;
}

// Controls the units not controled by the player.
void battle::ai(void) {
   cell *temp;
   temp = getAttackCell();

   if (temp) { // Attack a unit
      moveCreature(temp);
      selectedUnit->attack( *temp->getCreature() );
      selectedUnit->getPosition()->unselect();
      if ( temp->getCreature()->getNumber() == 0 ) {
         removeCreature( *temp->getCreature() );
         temp->setCreature(NULL);
      }
      if ( selectedUnit->getNumber() == 0) {
         removeCreature( *temp->getCreature() );
         selectedUnit->getPosition()->setCreature(NULL);
      }
      finishTurn();
   } else { // Move the unit
      int x, y;
      selectedUnit->getPosition()->getCoordinates(x, y);
      x=0;
      while(!battleMap[x][y].canMoveHere() && x<sizeX) x++;
      if (x!=sizeX) {
         moveCreature(&battleMap[x][y]);
         finishTurn();
      } else {
         selectedUnit->getPosition()->unselect();
         finishTurn();
      }
   }
}

// Constructor
battle::battle(hero &player, unit **enemies, int numberEnemies) : map(18, 9) {
   this->player = &player;
   // Set enemy creatures
   for (int i=0; i<numberEnemies && i<MAX_CREATURES; i++) {
      creatures[i] = enemies[i];
   }
   if (numberEnemies<MAX_CREATURES) {
      for (int j=numberEnemies; j<MAX_CREATURES; j++) creatures[j] = NULL;
   }

   for (int t=0; t<MAX_BATTLE_UNITS; t++) turns[t] = 0;

   endBattle = false;

   setHero(player);
   setCreatures();
   setTerrain("grassland-r1");
}

// Starts the battle.
void battle::start(void) {
   screen->erase();
   // Set first turn.
   selectedUnit = nextTurn();
   selectedUnit->getPosition()->select();

   /// @todo Use the loop function in loop.hpp
   bool done = false;
   timer fps;

   while (!done) {
      fps.start();
      input->readInput();
      done = frame();
      screen->update();
      fps.end(30);
   }
}

// Creates and starts a battle.
void createBattle(void) {
   hero *player;
   unit *creature[9];
   unit *temp;

   player = new hero(FIGHTER, HUMAN);
   for (int i=0; i<5; i++) {
      creature[i] = new unit(SKELETON, 5);
   }
   for (int t=5; t<9; t++) {
      creature[t] = new unit(BAT, 1);
   }
   for (int j=0; j<9; j++) {
      temp = new unit(SERGEANT, 3);
      player->recruitCreature(temp);
   }

   battle war(*player, creature, 9);
   war.start();
   //war.results(&player, &creature);

   // Free memory
   /*if (player) delete player;
   for (int i=0; i<9; i++) {
      if (creature[i]) delete creature[i];
   }*/
}
