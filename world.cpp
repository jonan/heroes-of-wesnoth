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

#include <fstream>
#include <iostream>
#include <string>

#include <SDL/SDL.h>

#include "battle.hpp"
#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "hero.hpp"
#include "timer.hpp"
#include "unit.hpp"
#include "world.hpp"

using namespace std;

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool world::frame(void) {
   if (keys[SDLK_ESCAPE]) endWorld = true;
   if (keys[SDLK_UP]) if (firstCell.y!=0) firstCell.y--;
   if (keys[SDLK_DOWN]) if (firstCell.y!=sizeY-9) firstCell.y++;
   if (keys[SDLK_LEFT]) if (firstCell.x!=0) firstCell.x--;
   if (keys[SDLK_RIGHT]) if (firstCell.x!=sizeX-18) firstCell.x++;
   moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   draw();
   return endWorld;
}

// Function to execute when the cell where the mouse is over is detected.
void world::mouseOver(const int x, const int y, const int button) {
   if ( button == 1  &&  (selectedUnit->getPosition() != &battleMap[x][y]) ) {
      if ( battleMap[x][y].canMoveHere() ) {
         moveCreature(&battleMap[x][y]);
         nextTurn();
      } else if ( battleMap[x][y].canAttackHere() ) {
         if ( battleMap[x][y].getCreature()->getMaster() != selectedUnit->getMaster() ) {
            moveCreature(&battleMap[x][y]);
            createFastBattle((hero&)(*selectedUnit), battleMap[x][y].getCreature()->getType());
            nextTurn();
         }
      }
   }
}

// Starts the next turn.
void world::nextTurn(void) {
   // Check if the battle has ended
   if (players[0]==NULL) endWorld = true;
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

// Constructor
world::world(const char *mapFile, const int x, const int y) : map(x, y) {
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
   while (j<sizeY) {
      file.get(temp);
      if (temp != '\n') {
         setTerrain(temp-48, i, j); // 48 is 0 in ASCII
         i++;
         if (i == sizeX) {
            i = 0;
            j++;
         }
      }
   }

   file.close();

   turn = -1;
   endWorld = false;
}

// Puts the enemies in the map.
void world::setEnemies(const char *enemiesMapFile) {
   // Create a string with the fisical location of the file
   // "map/" + name
   string map = "maps/";
   string fileName(enemiesMapFile);
   string fileDir = map + enemiesMapFile;

   ifstream file(fileDir.c_str(), ifstream::in);
   if (file.fail()) {
      cout << "Error opening map \"" << enemiesMapFile << "\"\n\n";
      exit(EXIT_FAILURE);
   }

   // Set the enemies
   char temp;
   int i = 0;
   int j = 0;
   while (j<sizeY) {
      file.get(temp);
      if (temp != '\n') {
         if (temp != '0') {
            unit *creature;
            creature = new unit(temp - 49, 0); // 49 is 1 in ASCII
            battleMap[i][j].setCreature(creature);
         }
         i++;
         if (i == sizeX) {
            i = 0;
            j++;
         }
      }
   }

   file.close();
}

// Puts a hero in the map.
void world::setHero(hero &player, const int x, const int y) {
   players.push_back(&player);
   battleMap[x][y].setCreature(&player);
}

// Creates and starts mission 1.
void mission1(void) {
   unit *temp;

   hero player(FIGHTER, HUMAN);
   world war("mission1", 30, 15);

   // Set the hero's units.
   for (int j=0; j<9; j++) {
      temp = new unit(SERGEANT, 10);
      player.recruitCreature(temp);
   }

   war.setEnemies("mission1_creatures");
   war.setHero(player, 1, 1);
   war.start();
}

// Creates and starts mission 1.
void mission2(void) {
   unit *temp;

   hero player(FIGHTER, HUMAN);
   world war("mission2", 30, 20);

   // Set the hero's units.
   for (int j=0; j<9; j++) {
      temp = new unit(SERGEANT, 10);
      player.recruitCreature(temp);
   }

   war.setEnemies("mission2_creatures");
   war.setHero(player, 3, 5);
   war.start();
}
