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

#include "cell.hpp"
#include "graphics.hpp"
#include "map.hpp"

// Indicates the terrain image of the map.
void map::setTerrain(const int terrainName, const int x, const int y) {
   SDL_Surface **terrain;
   int images; // Number of different images of a terrain.
   int movementPenalty;
   int randomNumber;

   if (terrainName == GRASS) {
      images = 8;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("grass-r1");
      terrain[1] = screen->getImage("grass-r2");
      terrain[2] = screen->getImage("grass-r3");
      terrain[3] = screen->getImage("grass-r4");
      terrain[4] = screen->getImage("grass-r5");
      terrain[5] = screen->getImage("grass-r6");
      terrain[6] = screen->getImage("grass-r7");
      terrain[7] = screen->getImage("grass-r8");
   }

   if (x == -1 && y ==-1) {
      for (int i=0; i<sizeX; i++) {
         for (int j=0; j<sizeY; j++) {
            randomNumber = rand() % images;
            battleMap[i][j].setTerrain(*terrain[randomNumber]);
            battleMap[i][j].setMovementPenalty(movementPenalty);
         }
      }
   } else {
      randomNumber = rand() % images;
      battleMap[x][y].setTerrain(*terrain[randomNumber]);
      battleMap[x][y].setMovementPenalty(movementPenalty);
   }
}
