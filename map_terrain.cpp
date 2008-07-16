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

   alpha = screen->getImage("alpha", 50);
   numberStars = 7;
   stars = new SDL_Surface*[numberStars];
   stars[0] = screen->getImage("terrain/stars/blue1");
   stars[1] = screen->getImage("terrain/stars/blue2");
   stars[2] = screen->getImage("terrain/stars/blue3");
   stars[3] = screen->getImage("terrain/stars/blue4");
   stars[4] = screen->getImage("terrain/stars/blue5");
   stars[5] = screen->getImage("terrain/stars/blue6");
   stars[6] = screen->getImage("terrain/stars/blue7");
   // Set the varibles depending of the tipe of terrain.
   if (terrainName == CAVE_FLOOR) {
      images = 6;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/cave/floor");
      terrain[1] = screen->getImage("terrain/cave/floor2");
      terrain[2] = screen->getImage("terrain/cave/floor3");
      terrain[3] = screen->getImage("terrain/cave/floor4");
      terrain[4] = screen->getImage("terrain/cave/floor5");
      terrain[5] = screen->getImage("terrain/cave/floor6");
   } else if (terrainName == CAVE_HILLS) {
      images = 3;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/cave/hills-variation");
      terrain[1] = screen->getImage("terrain/cave/hills-variation2");
      terrain[2] = screen->getImage("terrain/cave/hills-variation3");
   } else if (terrainName == DESERT) {
      images = 8;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/desert");
      terrain[1] = screen->getImage("terrain/desert/desert2");
      terrain[2] = screen->getImage("terrain/desert/desert3");
      terrain[3] = screen->getImage("terrain/desert/desert4");
      terrain[4] = screen->getImage("terrain/desert/desert5");
      terrain[5] = screen->getImage("terrain/desert/desert6");
      terrain[6] = screen->getImage("terrain/desert/desert7");
      terrain[7] = screen->getImage("terrain/desert/desert8");
   } else if (terrainName == DESERT_HILLS) {
      images = 3;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/desert-hills");
      terrain[1] = screen->getImage("terrain/desert/desert-hills2");
      terrain[2] = screen->getImage("terrain/desert/desert-hills3");
   } else if (terrainName == DESERT_MOUNTAIN) {
      images = 3;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/desert-mountain-peak1");
      terrain[1] = screen->getImage("terrain/desert/desert-mountain-peak2");
      terrain[2] = screen->getImage("terrain/desert/desert-mountain-peak3");
   } else if (terrainName == DESERT_ROAD) {
      images = 1;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/desert-road");
   } else if (terrainName == DESERT_SAND) {
      images = 8;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/sand");
      terrain[1] = screen->getImage("terrain/desert/sand2");
      terrain[2] = screen->getImage("terrain/desert/sand3");
      terrain[3] = screen->getImage("terrain/desert/sand4");
      terrain[4] = screen->getImage("terrain/desert/sand5");
      terrain[5] = screen->getImage("terrain/desert/sand6");
      terrain[6] = screen->getImage("terrain/desert/sand7");
      terrain[7] = screen->getImage("terrain/desert/sand8");
   } else if (terrainName == FLAT_DIRT) {
      images = 1;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/dirt");
   } else if (terrainName == FLAT_GRASS) {
      images = 8;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/grass-r1");
      terrain[1] = screen->getImage("terrain/flat/grass-r2");
      terrain[2] = screen->getImage("terrain/flat/grass-r3");
      terrain[3] = screen->getImage("terrain/flat/grass-r4");
      terrain[4] = screen->getImage("terrain/flat/grass-r5");
      terrain[5] = screen->getImage("terrain/flat/grass-r6");
      terrain[6] = screen->getImage("terrain/flat/grass-r7");
      terrain[7] = screen->getImage("terrain/flat/grass-r8");
   } else if (terrainName == FLAT_ROAD) {
      images = 3;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/road");
      terrain[1] = screen->getImage("terrain/flat/road2");
      terrain[2] = screen->getImage("terrain/flat/road3");
   } else if (terrainName == FLAT_SAVANNA) {
      images = 3;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/savanna");
      terrain[1] = screen->getImage("terrain/flat/savanna2");
      terrain[2] = screen->getImage("terrain/flat/savanna3");
   } else if (terrainName == FLAT_STONE_PATH) {
      images = 6;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/stone-path");
      terrain[1] = screen->getImage("terrain/flat/stone-path2");
      terrain[2] = screen->getImage("terrain/flat/stone-path3");
      terrain[3] = screen->getImage("terrain/flat/stone-path4");
      terrain[4] = screen->getImage("terrain/flat/stone-path5");
      terrain[5] = screen->getImage("terrain/flat/stone-path6");
   } else if (terrainName == HILLS) {
      images = 3;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/hills-variation");
      terrain[1] = screen->getImage("terrain/hills-variation2");
      terrain[2] = screen->getImage("terrain/hills-variation3");
   } else if (terrainName == LAVA) {
      images = 3;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/lava");
      terrain[1] = screen->getImage("terrain/lava2");
      terrain[2] = screen->getImage("terrain/lava3");
   } else if (terrainName == WATER_COAST) {
      images = 3;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/coast");
      terrain[1] = screen->getImage("terrain/water/coast2");
      terrain[2] = screen->getImage("terrain/water/coast3");
   } else if (terrainName == WATER_FORD) {
      images = 2;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/ford");
      terrain[1] = screen->getImage("terrain/water/ford2");
   } else if (terrainName == WATER_OCEAN) {
      images = 3;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/ocean");
      terrain[1] = screen->getImage("terrain/water/ocean2");
      terrain[2] = screen->getImage("terrain/water/ocean3");
   } else if (terrainName == WATER_ICE) {
      images = 6;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/ice");
      terrain[1] = screen->getImage("terrain/water/ice2");
      terrain[2] = screen->getImage("terrain/water/ice3");
      terrain[3] = screen->getImage("terrain/water/ice4");
      terrain[4] = screen->getImage("terrain/water/ice5");
      terrain[5] = screen->getImage("terrain/water/ice6");
   } else if (terrainName == WATER_SNOW) {
      images = 2;
      movementPenalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/snow");
      terrain[1] = screen->getImage("terrain/water/snow2");
   } else if (terrainName == WATER_SNOW_HILLS) {
      images = 3;
      movementPenalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/snow-hills");
      terrain[1] = screen->getImage("terrain/water/snow-hills2");
      terrain[2] = screen->getImage("terrain/water/snow-hills2");
   } else {
      cout << "\n\tWrong terrain type : " << terrainName << "\n\n";
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
