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

#include <SDL/SDL.h>

#include "cell.hpp"
#include "graphics.hpp"
#include "map.hpp"

using namespace std;

#define ADD_CAVE_FLOOR          0
#define ADD_FLAT_GRASS          1
#define ADD_FLAT_GRASS_TO_WATER 2
#define ADD_FLAT_ROAD           3
#define ADD_WATER_COAST         4
#define ADD_WATER_OCEAN         5

/**
CAVE_PATH
CAVE_FLOOR
FLAT_GRASS
FLAT_ROAD
FORD
WATER_COAST
WATER_OCEAN
*/
/*

CAVE_PATH vs CAVE_FLOOR -> CAVE_FLOOR
CAVE_PATH vs FLAT_GRASS -> FLAT_GRASS
CAVE_PATH vs FLAT_ROAD -> FLAT_ROAD
CAVE_PATH vs FORD -> FORD
CAVE_PATH vs WATER_COAST -> WATER_COAST
CAVE_PATH vs WATER_OCEAN -> WATER_OCEAN

CAVE_FLOOR vs FLAT_GRASS -> CAVE_FLOOR
CAVE_FLOOR vs FLAT_ROAD -> CAVE_FLOOR
CAVE_FLOOR vs FORD -> CAVE_FLOOR
CAVE_FLOOR vs WATER_COAST -> CAVE_FLOOR
CAVE_FLOOR vs WATER_OCEAN -> CAVE_FLOOR

FLAT_GRASS vs FLAT_ROAD -> FLAT_GRASS
FLAT_GRASS vs FORD -> FLAT_GRASS
FLAT_GRASS vs WATER_COAST -> FLAT_GRASS
FLAT_GRASS vs WATER_OCEAN -> FLAT_GRASS

FLAT_ROAD vs FORD -> FLAT_ROAD
FLAT_ROAD vs WATER_COAST -> FLAT_ROAD
FLAT_ROAD vs WATER_OCEAN -> FLAT_ROAD

FORD vs WATER_COAST -> WATER_COAST
FORD vs WATER_OCEAN -> WATER_OCEAN

WATER_COAST vs WATER_OCEAN -> WATER_COAST

*/

// Sets the images needed to soften the map.
void initializeVariables(SDL_Surface **one, SDL_Surface **two,
                         SDL_Surface **three, SDL_Surface **four,
                         int type
                        ) {
   if (type == ADD_CAVE_FLOOR) {
      one[0] = screen->getImage("terrain/cave/floor-n");
      one[1] = screen->getImage("terrain/cave/floor-ne");
      one[2] = screen->getImage("terrain/cave/floor-se");
      one[3] = screen->getImage("terrain/cave/floor-s");
      one[4] = screen->getImage("terrain/cave/floor-sw");
      one[5] = screen->getImage("terrain/cave/floor-nw");

      two[0] = screen->getImage("terrain/cave/floor-n-ne");
      two[1] = screen->getImage("terrain/cave/floor-ne-se");
      two[2] = screen->getImage("terrain/cave/floor-se-s");
      two[3] = screen->getImage("terrain/cave/floor-s-sw");
      two[4] = screen->getImage("terrain/cave/floor-sw-nw");
      two[5] = screen->getImage("terrain/cave/floor-nw-n");

      *three = NULL;
      *four = NULL;
   } else if (type == ADD_FLAT_GRASS) {
      one[0] = screen->getImage("terrain/flat/grass-n");
      one[1] = screen->getImage("terrain/flat/grass-ne");
      one[2] = screen->getImage("terrain/flat/grass-se");
      one[3] = screen->getImage("terrain/flat/grass-s");
      one[4] = screen->getImage("terrain/flat/grass-sw");
      one[5] = screen->getImage("terrain/flat/grass-nw");

      two[0] = screen->getImage("terrain/flat/grass-n-ne");
      two[1] = screen->getImage("terrain/flat/grass-ne-se");
      two[2] = screen->getImage("terrain/flat/grass-se-s");
      two[3] = screen->getImage("terrain/flat/grass-s-sw");
      two[4] = screen->getImage("terrain/flat/grass-sw-nw");
      two[5] = screen->getImage("terrain/flat/grass-nw-n");

      three[0] = screen->getImage("terrain/flat/grass-n-ne-se");
      three[1] = screen->getImage("terrain/flat/grass-ne-se-s");
      three[2] = screen->getImage("terrain/flat/grass-se-s-sw");
      three[3] = screen->getImage("terrain/flat/grass-s-sw-nw");
      three[4] = screen->getImage("terrain/flat/grass-sw-nw-n");
      three[5] = screen->getImage("terrain/flat/grass-nw-n-ne");

      *four = NULL;
   } else if (type == ADD_FLAT_GRASS_TO_WATER) {
      one[0] = screen->getImage("terrain/flat/grass-to-water-n");
      one[1] = screen->getImage("terrain/flat/grass-to-water-ne");
      one[2] = screen->getImage("terrain/flat/grass-to-water-se");
      one[3] = screen->getImage("terrain/flat/grass-to-water-s");
      one[4] = screen->getImage("terrain/flat/grass-to-water-sw");
      one[5] = screen->getImage("terrain/flat/grass-to-water-nw");

      two[0] = screen->getImage("terrain/flat/grass-to-water-n-ne");
      two[1] = screen->getImage("terrain/flat/grass-to-water-ne-se");
      two[2] = screen->getImage("terrain/flat/grass-to-water-se-s");
      two[3] = screen->getImage("terrain/flat/grass-to-water-s-sw");
      two[4] = screen->getImage("terrain/flat/grass-to-water-sw-nw");
      two[5] = screen->getImage("terrain/flat/grass-to-water-nw-n");

      three[0] = screen->getImage("terrain/flat/grass-to-water-n-ne-se");
      three[1] = screen->getImage("terrain/flat/grass-to-water-ne-se-s");
      three[2] = screen->getImage("terrain/flat/grass-to-water-se-s-sw");
      three[3] = screen->getImage("terrain/flat/grass-to-water-s-sw-nw");
      three[4] = screen->getImage("terrain/flat/grass-to-water-sw-nw-n");
      three[5] = screen->getImage("terrain/flat/grass-to-water-nw-n-ne");

      four[0] = screen->getImage("terrain/flat/grass-to-water-n-ne-se-s");
      four[1] = screen->getImage("terrain/flat/grass-to-water-ne-se-s-sw");
      four[2] = screen->getImage("terrain/flat/grass-to-water-se-s-sw-nw");
      four[3] = screen->getImage("terrain/flat/grass-to-water-s-sw-nw-n");
      four[4] = screen->getImage("terrain/flat/grass-to-water-sw-nw-n-ne");
      four[5] = screen->getImage("terrain/flat/grass-to-water-nw-n-ne-se");
   } else if (type == ADD_FLAT_ROAD) {
      one[0] = screen->getImage("terrain/flat/road-n");
      one[1] = screen->getImage("terrain/flat/road-ne");
      one[2] = screen->getImage("terrain/flat/road-se");
      one[3] = screen->getImage("terrain/flat/road-s");
      one[4] = screen->getImage("terrain/flat/road-sw");
      one[5] = screen->getImage("terrain/flat/road-nw");

      two[0] = screen->getImage("terrain/flat/road-n-ne");
      two[1] = screen->getImage("terrain/flat/road-ne-se");
      two[2] = screen->getImage("terrain/flat/road-se-s");
      two[3] = screen->getImage("terrain/flat/road-s-sw");
      two[4] = screen->getImage("terrain/flat/road-sw-nw");
      two[5] = screen->getImage("terrain/flat/road-nw-n");

      *three = NULL;
      *four = NULL;
   } else if (type == ADD_WATER_COAST) {
      one[0] = screen->getImage("terrain/water/coast-n");
      one[1] = screen->getImage("terrain/water/coast-ne");
      one[2] = screen->getImage("terrain/water/coast-se");
      one[3] = screen->getImage("terrain/water/coast-s");
      one[4] = screen->getImage("terrain/water/coast-sw");
      one[5] = screen->getImage("terrain/water/coast-nw");

      *two = NULL;
      *three = NULL;
      *four = NULL;
   } else if (type == ADD_WATER_OCEAN) {
      one[0] = screen->getImage("terrain/water/ocean-n");
      one[1] = screen->getImage("terrain/water/ocean-ne");
      one[2] = screen->getImage("terrain/water/ocean-se");
      one[3] = screen->getImage("terrain/water/ocean-s");
      one[4] = screen->getImage("terrain/water/ocean-sw");
      one[5] = screen->getImage("terrain/water/ocean-nw");

      *two = NULL;
      *three = NULL;
      *four = NULL;
   }
}

// Adds the necesary images to soften the map.
void addImages(bool *terrain, cell &mapCell, SDL_Surface **one, SDL_Surface **two, SDL_Surface **three, SDL_Surface **four) {
   int position = 0;
   while (!terrain[position]) position++;
   while (position<6) {
      terrain[position] = false;
      if (position!=0 || !terrain[NW]) {
         if (terrain[position+1] && *two!=NULL) {
            terrain[position+1] = false;
            if (terrain[position+2] && *three!=NULL) {
               terrain[position+2] = false;
               if (terrain[position+3] && *four!=NULL) {
                  terrain[position+3] = false;
                  mapCell.addImage( *four[position] );
               } else
                  mapCell.addImage( *three[position] );
            } else
               mapCell.addImage( *two[position] );
         } else
            mapCell.addImage( *one[position] );
      } else if (*two!=NULL){
         terrain[NW] = false;
         if (terrain[SW] && *three!=NULL) {
            terrain[SW] = false;
            if (terrain[S] && *four!=NULL) {
               terrain[S] = false;
               mapCell.addImage( *four[S] );
            } else if (terrain[NE] && *four!=NULL) {
               terrain[NE] = false;
               mapCell.addImage( *four[SW] );
            } else
               mapCell.addImage( *three[SW] );
         } else if (terrain[NE] && *three!=NULL) {
            terrain[NE] = false;
            if (terrain[SE] && *four!=NULL) {
               terrain[SE] = false;
               mapCell.addImage( *four[NW] );
            } else
               mapCell.addImage( *three[NW] );
         } else
            mapCell.addImage( *two[NW] );
      } else mapCell.addImage( *one[position] );
      while (!terrain[position] && position<7) position++;
   }
}

// Softens a type of terrain.
void map::softenTerrain(const char cellTerrain, char *terrain, const int numberTerrains, const int softImages) {
   SDL_Surface *one[6];
   SDL_Surface *two[6];
   SDL_Surface *three[6];
   SDL_Surface *four[6];
   cell *temp;
   bool differentTerrain[7];
   bool needSoft = false; // Indicates if the cell needs to be soften

   for (int j=0; j<7; j++) differentTerrain[j] = false;
   initializeVariables(one, two, three, four, softImages);

   for (int x=0; x<width; x++)
      for (int y=0; y<height; y++) {
         for (int i=0; i<numberTerrains; i++)
            needSoft = ( needSoft || (battleMap[x][y].getTerrain() == terrain[i]) );
         if (needSoft) {
            needSoft = false; // Reset for next cell
            for (int i=N; i<=NW; i++) {
               temp = battleMap[x][y].getConnectedCell(i);
               if (temp != NULL)
                  if(temp->getTerrain() == cellTerrain) differentTerrain[i] = true;
            }
            addImages(differentTerrain, battleMap[x][y], one, two, three, four);
         }
      }
}

// Softens the map to make it look nicer.
void map::softenMap(void) {
   char *terrain;

   terrain = new char[3];
   terrain[0] = CAVE_PATH;
   terrain[1] = FORD;
   terrain[2] = WATER_OCEAN;
   softenTerrain(WATER_COAST, terrain, 3, ADD_WATER_COAST);

   delete [] terrain;
   terrain = new char[2];
   terrain[0] = CAVE_PATH;
   terrain[1] = FORD;
   softenTerrain(WATER_OCEAN, terrain, 2, ADD_WATER_OCEAN);

   delete [] terrain;
   terrain = new char[6];
   terrain[0] = CAVE_PATH;
   terrain[1] = FLAT_GRASS;
   terrain[2] = FLAT_ROAD;
   terrain[3] = FORD;
   terrain[4] = WATER_COAST;
   terrain[5] = WATER_OCEAN;
   softenTerrain(CAVE_FLOOR, terrain, 6, ADD_CAVE_FLOOR);

   delete [] terrain;
   terrain = new char[2];
   terrain[0] = CAVE_PATH;
   terrain[1] = FLAT_ROAD;
   softenTerrain(FLAT_GRASS, terrain, 2, ADD_FLAT_GRASS);

   delete [] terrain;
   terrain = new char[3];
   terrain[0] = FORD;
   terrain[1] = WATER_COAST;
   terrain[2] = WATER_OCEAN;
   softenTerrain(FLAT_GRASS, terrain, 3, ADD_FLAT_GRASS_TO_WATER);

   delete [] terrain;
   terrain = new char[4];
   terrain[0] = CAVE_PATH;
   terrain[1] = FORD;
   terrain[2] = WATER_COAST;
   terrain[3] = WATER_OCEAN;
   softenTerrain(FLAT_ROAD, terrain, 4, ADD_FLAT_ROAD);

   delete [] terrain;
}
