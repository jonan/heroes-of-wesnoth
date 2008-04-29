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

#include "graphics.hpp"
#include "map.hpp"

// Indicates the terrain image of the map.
void map::setTerrain(const int terrainName) {
   SDL_Surface **terrain;
   int randomNumber;

   if (terrainName == GRASS) {
      terrain = new SDL_Surface*[8];
      terrain[0] = screen->getImage("grass-r1");
      terrain[1] = screen->getImage("grass-r2");
      terrain[2] = screen->getImage("grass-r3");
      terrain[3] = screen->getImage("grass-r4");
      terrain[4] = screen->getImage("grass-r5");
      terrain[5] = screen->getImage("grass-r6");
      terrain[6] = screen->getImage("grass-r7");
      terrain[7] = screen->getImage("grass-r8");
      for (int x=0; x<sizeX; x++)
         for (int y=0; y<sizeY; y++) {
            randomNumber = rand() % 8;
            battleMap[x][y].setTerrain(*terrain[randomNumber]);
            battleMap[x][y].setMovementPenalty(1);
         }
   }
}
