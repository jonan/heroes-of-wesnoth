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
#include <iostream>

#include <SDL/SDL.h>

#include "cell.hpp"
#include "graphics.hpp"
#include "map.hpp"

using namespace std;

// Indicates the terrain image of the map. Specify only the terrainName
// attribute to apply the terrain to all the cells of the map.
void map::setTerrain(const char terrainName, const int x, const int y) {
   SDL_Surface **terrain, **stars, *alpha;
   int images, numberStars; // Number of different images of a terrain.
   int movementPenalty;
   int randomNumber;

   alpha = screen->getImage("alpha");
   numberStars = 7;
   stars = new SDL_Surface*[numberStars];
   stars[0] = screen->getImage("terrain/blue1");
   stars[1] = screen->getImage("terrain/blue2");
   stars[2] = screen->getImage("terrain/blue3");
   stars[3] = screen->getImage("terrain/blue4");
   stars[4] = screen->getImage("terrain/blue5");
   stars[5] = screen->getImage("terrain/blue6");
   stars[6] = screen->getImage("terrain/blue7");
   // Set the varibles depending of the tipe of terrain.
   if (terrainName == CAVE) {
      images = 6;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/floor");
      terrain[1] = screen->getImage("terrain/floor2");
      terrain[2] = screen->getImage("terrain/floor3");
      terrain[3] = screen->getImage("terrain/floor4");
      terrain[4] = screen->getImage("terrain/floor5");
      terrain[5] = screen->getImage("terrain/floor6");
   } else if (terrainName == GRASS) {
      images = 8;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/grass-r1");
      terrain[1] = screen->getImage("terrain/grass-r2");
      terrain[2] = screen->getImage("terrain/grass-r3");
      terrain[3] = screen->getImage("terrain/grass-r4");
      terrain[4] = screen->getImage("terrain/grass-r5");
      terrain[5] = screen->getImage("terrain/grass-r6");
      terrain[6] = screen->getImage("terrain/grass-r7");
      terrain[7] = screen->getImage("terrain/grass-r8");
   } else if (terrainName == WATER) {
      images = 1;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/ford");
   } else {
      cout << "Wrong terrain type : " << terrainName << "\n\n";
      exit(EXIT_FAILURE);
   }

   if (x == -1 && y ==-1) { // Set the attributes to all the cells.
      for (int i=0; i<width; i++)
         for (int j=0; j<height; j++) {
            battleMap[i][j].setAlpha(*alpha);
            randomNumber = rand() % numberStars;
            battleMap[i][j].setStars(*stars[randomNumber]);
            randomNumber = rand() % images;
            battleMap[i][j].addImage(*terrain[randomNumber], terrainName);
            battleMap[i][j].setMovementPenalty(movementPenalty);
         }
   } else { // Set the attributes to a given cell.
      battleMap[x][y].setAlpha(*alpha);
      randomNumber = rand() % numberStars;
      battleMap[x][y].setStars(*stars[randomNumber]);
      randomNumber = rand() % images;
      battleMap[x][y].addImage(*terrain[randomNumber], terrainName);
      battleMap[x][y].setMovementPenalty(movementPenalty);
   }
}
