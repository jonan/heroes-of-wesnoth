/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007  Jon Ander Peñalba <jonan88@gmail.com>

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

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool battle::frame(void) {
   if (keys[SDLK_ESCAPE]) endBattle = true;
   moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   draw();
   return endBattle;
}

// Puts the enemy creatures in the map.
void battle::setCreatures(void) {
   for (int i=0; i<MAX_CREATURES; i++)
      battleMap[sizeX-2][i].setCreature(creatures[i]);
}

// Function to execute when the cell where the mouse is over is detected.
void battle::mouseOver(int x, int y, int button) {
   battleMap[x][y].putMouse();
   mouseOverCell = &battleMap[x][y];
   if ( button == 1  &&  selectedCell != &battleMap[x][y] ) {
      if ( battleMap[x][y].canMoveHere() ) {
         moveCreature(&battleMap[x][y]);
         finishTurn();
      } else if ( battleMap[x][y].canAttackHere() ) {
         if ( battleMap[x][y].getCreature()->getMaster() != selectedCell->getCreature()->getMaster() ) {
            selectedCell->getCreature()->attack( *battleMap[x][y].getCreature() );
            if ( battleMap[x][y].getCreature()->getNumber() == 0 ) {
               removeCreature(battleMap[x][y].getCreature());
               battleMap[x][y].killCreature();
            }
            if ( selectedCell->getCreature()->getNumber() == 0) {
               removeCreature(battleMap[x][y].getCreature());
               selectedCell->killCreature();
            }
            selectedCell->unselect();
            finishTurn();
         }
      }
   }
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
               if (creatures[i-1]) {
                  done = true;
                  turn = i;
                  return creatures[i-1];
               }
            }
         }
      // Increase all the turns
      for (int j=0; j<MAX_BATTLE_UNITS; j++) {
         if (j==0) {
            if (player)
               turns[j] += player->getAgility();
         } else if (j<MAX_CREATURES+1) {
            if (creatures[j-1])
               turns[j] += creatures[j-1]->getAgility();
         }
      }
   }
}

// Function to call when a turn ends.
void battle::finishTurn(void) {
   selectedCell = nextTurn()->getPosition()->select();
   // Wait until the mouse button is released.
   while (mouse[BUTTON]) input->readInput();
}

// Moves the selected creature to a given cell.
void battle::moveCreature(cell *endPosition) {
   endPosition->setCreature( selectedCell->getCreature() );
   selectedCell->unselect();
   selectedCell->setCreature(NULL);
}

// Removes a unit from the battle.
void battle::removeCreature(unit* creature) {
   bool found = false;
   int i = 0;

   while (i<MAX_BATTLE_UNITS && !found) {
      if (i==0) {
         if (player == creature) {
            player = NULL;
            found = true;
         }
      } else if (i<MAX_CREATURES+1) {
         if (creatures[i-1] == creature) {
            creatures[i-1] = NULL;
            found = true;
         }
      }
      i++;
   }
}

// Constructor
battle::battle(hero *player, unit **enemies, int numberEnemies) : map(18, 9) {
   this->player = player;
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
   selectedCell = nextTurn()->getPosition()->select();

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

   player = new hero(FIGHTER, HUMAN);
   for (int i=0; i<9; i++) {
      creature[i] = new unit(SKELETON, 1);
   }

   battle war(player, creature, 9);
   war.start();
   //war.results(&player, &creature);

   // Free memory
   /*if (player) delete player;
   for (int i=0; i<9; i++) {
      if (creature[i]) delete creature[i];
   }*/
}
