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

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include <SDL/SDL.h>

#include "battle.hpp"
#include "cell.hpp"
#include "events.hpp"
#include "hero.hpp"
#include "world.hpp"

using namespace std;

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool world::frame(void) {
   if (keys[SDLK_ESCAPE]) {
      while (keys[SDLK_ESCAPE]) input->readInput();
      endWorld = true;
   } else {
      draw();
      moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   }
   return endWorld;
}

// Function to execute when the user clicks on a cell.
void world::mouseClick(const int x, const int y) {
   if ( selectedUnit->getPosition() != &battleMap[x][y] ) {
      if ( battleMap[x][y].canMoveHere() ) {
         moveCreature(battleMap[x][y]);
         battleMap[x][y].calculateView(players[turn]->getVisibility());
         nextTurn();
      } else if ( battleMap[x][y].canAttackHere() ) {
         if ( battleMap[x][y].getCreature()->getMaster() != selectedUnit->getMaster() ) {
            moveCreature(battleMap[x][y]);
            battleMap[x][y].calculateView(players[turn]->getVisibility());

            // Set the battle information
            hero *player = (hero*)(selectedUnit);
            int creatureType = battleMap[x][y].getCreature()->getType();
            int terrain = battleMap[x][y].getTerrain();
            // Start the battle
            if ( createBattle(*player, creatureType, terrain) )
               deleteCreature(battleMap[x][y]);
            else players[turn] = NULL;

            nextTurn();
         }
      }
   }
}

// Starts the next turn.
void world::nextTurn(void) {
   // Check if the battle has ended
   if (players[0]==NULL || numberEnemies == 0) endWorld = true;
   // If the battle hasn't ended continue
   if (!endWorld) {
      turn++;
      if (turn==players.size()) turn = 0;
      selectedUnit = players[turn];
      selectedUnit->getPosition()->select();
      // Wait until the mouse button is released.
      while (mouse[BUTTON]) input->readInput();
   }
}


// Puts the enemies in the map.
void world::setEnemies(const char *mapFile) {
   // Create a string with the fisical location of the file
   // "map/" + name
   string map = "maps/";
   string fileName(mapFile);
   string fileDir = map + mapFile + "_creatures";

   ifstream file(fileDir.c_str(), ifstream::in);
   if (file.fail()) {
      cout << "Error opening map \"" << mapFile << "\"\n\n";
      exit(EXIT_FAILURE);
   }

   // Set the enemies
   numberEnemies = 0;
   char temp;
   int i = 0;
   int j = 0;
   while (j<height) {
      file.get(temp);
      if (temp != '\n') {
         if (temp != '-') {
            unit *creature;
            /// @todo Free this units if they are not killed.
            creature = new unit(temp, 0);
            battleMap[i][j].setCreature(creature);
            numberEnemies++;
         }
         i++;
         if (i == width) {
            i = 0;
            j++;
         }
      }
   }

   file.close();
}

// Removes a unit from the world and deletes it.
void world::deleteCreature(cell &position) {
   delete position.getCreature();
   position.setCreature(NULL);
   numberEnemies--;
}

// Constructor
world::world(const char *mapFile, const int width, const int height) : map(width, height) {
   // Create a string with the fisical location of the file
   // "map/" + name
   string map = "maps/";
   string fileName(mapFile);
   string fileDir = map + fileName;

   ifstream file(fileDir.c_str(), ifstream::in);
   if (file.fail()) {
      cout << "Error opening map \"" << mapFile << "\"\n\n";
      exit(EXIT_FAILURE);
   }

   // Set the terrain
   char temp;
   int i = 0;
   int j = 0;
   while (j<height) {
      file.get(temp);
      if (temp != '\n') {
         setTerrain(temp, i, j);
         i++;
         if (i == width) {
            i = 0;
            j++;
         }
      }
   }

   file.close();

   setEnemies(mapFile);
   softenMap();

   turn = -1;
   endWorld = false;
}

// Puts a hero in the map.
void world::setHero(hero &player, const int x, const int y) {
   players.push_back(&player);
   battleMap[x][y].setCreature(&player);
   battleMap[x][y].calculateView(player.getVisibility());
}
