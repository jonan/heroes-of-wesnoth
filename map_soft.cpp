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

#define ADD_CAVE_FLOOR              0
#define ADD_CAVE_HILLS              1
#define ADD_DESERT                  2
#define ADD_DESERT_HILLS            3
#define ADD_DESERT_MOUNTAIN         4
#define ADD_DESERT_ROAD             5
#define ADD_DESERT_SAND             6
#define ADD_FLAT_DIRT               7
#define ADD_FLAT_GRASS              8
#define ADD_FLAT_GRASS_TO_WATER     9
#define ADD_FLAT_ROAD              10
#define ADD_FLAT_SAVANNA           11
#define ADD_FLAT_SAVANNA_TO_WATER  12
#define ADD_FLAT_STONE_PATH        13
#define ADD_LAVA                   14
#define ADD_WATER_COAST            15
#define ADD_WATER_FORD             16
#define ADD_WATER_ICE              17
#define ADD_WATER_ICE_TO_WATER     18
#define ADD_WATER_OCEAN            19

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
   } else if (type == ADD_CAVE_HILLS) {
      one[0] = screen->getImage("terrain/cave/hills-n");
      one[1] = screen->getImage("terrain/cave/hills-ne");
      one[2] = screen->getImage("terrain/cave/hills-se");
      one[3] = screen->getImage("terrain/cave/hills-s");
      one[4] = screen->getImage("terrain/cave/hills-sw");
      one[5] = screen->getImage("terrain/cave/hills-nw");

      *two = NULL;
      *three = NULL;
      *four = NULL;
   } else if (type == ADD_DESERT) {
      one[0] = screen->getImage("terrain/desert/desert-n");
      one[1] = screen->getImage("terrain/desert/desert-ne");
      one[2] = screen->getImage("terrain/desert/desert-se");
      one[3] = screen->getImage("terrain/desert/desert-s");
      one[4] = screen->getImage("terrain/desert/desert-sw");
      one[5] = screen->getImage("terrain/desert/desert-nw");

      two[0] = screen->getImage("terrain/desert/desert-n-ne");
      two[1] = screen->getImage("terrain/desert/desert-ne-se");
      two[2] = screen->getImage("terrain/desert/desert-se-s");
      two[3] = screen->getImage("terrain/desert/desert-s-sw");
      two[4] = screen->getImage("terrain/desert/desert-sw-nw");
      two[5] = screen->getImage("terrain/desert/desert-nw-n");

      three[0] = screen->getImage("terrain/desert/desert-n-ne-se");
      three[1] = screen->getImage("terrain/desert/desert-ne-se-s");
      three[2] = screen->getImage("terrain/desert/desert-se-s-sw");
      three[3] = screen->getImage("terrain/desert/desert-s-sw-nw");
      three[4] = screen->getImage("terrain/desert/desert-sw-nw-n");
      three[5] = screen->getImage("terrain/desert/desert-nw-n-ne");

      *four = NULL;
   } else if (type == ADD_DESERT_HILLS) {
      one[0] = screen->getImage("terrain/desert/desert-hills-n");
      one[1] = screen->getImage("terrain/desert/desert-hills-ne");
      one[2] = screen->getImage("terrain/desert/desert-hills-se");
      one[3] = screen->getImage("terrain/desert/desert-hills-s");
      one[4] = screen->getImage("terrain/desert/desert-hills-sw");
      one[5] = screen->getImage("terrain/desert/desert-hills-nw");

      *two = NULL;
      *three = NULL;
      *four = NULL;
   } else if (type == ADD_DESERT_MOUNTAIN) {
      one[0] = screen->getImage("terrain/desert/desert-mountains-n");
      one[1] = screen->getImage("terrain/desert/desert-mountains-ne");
      one[2] = screen->getImage("terrain/desert/desert-mountains-se");
      one[3] = screen->getImage("terrain/desert/desert-mountains-s");
      one[4] = screen->getImage("terrain/desert/desert-mountains-sw");
      one[5] = screen->getImage("terrain/desert/desert-mountains-nw");

      *two = NULL;
      *three = NULL;
      *four = NULL;
   } else if (type == ADD_DESERT_ROAD) {
      one[0] = screen->getImage("terrain/desert/desert-road-n");
      one[1] = screen->getImage("terrain/desert/desert-road-ne");
      one[2] = screen->getImage("terrain/desert/desert-road-se");
      one[3] = screen->getImage("terrain/desert/desert-road-s");
      one[4] = screen->getImage("terrain/desert/desert-road-sw");
      one[5] = screen->getImage("terrain/desert/desert-road-nw");

      two[0] = screen->getImage("terrain/desert/desert-road-n-ne");
      two[1] = screen->getImage("terrain/desert/desert-road-ne-se");
      two[2] = screen->getImage("terrain/desert/desert-road-se-s");
      two[3] = screen->getImage("terrain/desert/desert-road-s-sw");
      two[4] = screen->getImage("terrain/desert/desert-road-sw-nw");
      two[5] = screen->getImage("terrain/desert/desert-road-nw-n");

      three[0] = screen->getImage("terrain/desert/desert-road-n-ne-se");
      three[1] = screen->getImage("terrain/desert/desert-road-ne-se-s");
      three[2] = screen->getImage("terrain/desert/desert-road-se-s-sw");
      three[3] = screen->getImage("terrain/desert/desert-road-s-sw-nw");
      three[4] = screen->getImage("terrain/desert/desert-road-sw-nw-n");
      three[5] = screen->getImage("terrain/desert/desert-road-nw-n-ne");

      *four = NULL;
   } else if (type == ADD_DESERT_SAND) {
      one[0] = screen->getImage("terrain/desert/sand-n");
      one[1] = screen->getImage("terrain/desert/sand-ne");
      one[2] = screen->getImage("terrain/desert/sand-se");
      one[3] = screen->getImage("terrain/desert/sand-s");
      one[4] = screen->getImage("terrain/desert/sand-sw");
      one[5] = screen->getImage("terrain/desert/sand-nw");

      two[0] = screen->getImage("terrain/desert/sand-n-ne");
      two[1] = screen->getImage("terrain/desert/sand-ne-se");
      two[2] = screen->getImage("terrain/desert/sand-se-s");
      two[3] = screen->getImage("terrain/desert/sand-s-sw");
      two[4] = screen->getImage("terrain/desert/sand-sw-nw");
      two[5] = screen->getImage("terrain/desert/sand-nw-n");

      three[0] = screen->getImage("terrain/desert/sand-n-ne-se");
      three[1] = screen->getImage("terrain/desert/sand-ne-se-s");
      three[2] = screen->getImage("terrain/desert/sand-se-s-sw");
      three[3] = screen->getImage("terrain/desert/sand-s-sw-nw");
      three[4] = screen->getImage("terrain/desert/sand-sw-nw-n");
      three[5] = screen->getImage("terrain/desert/sand-nw-n-ne");

      *four = NULL;
   } else if (type == ADD_FLAT_DIRT) {
      one[0] = screen->getImage("terrain/flat/dirt-n");
      one[1] = screen->getImage("terrain/flat/dirt-ne");
      one[2] = screen->getImage("terrain/flat/dirt-se");
      one[3] = screen->getImage("terrain/flat/dirt-s");
      one[4] = screen->getImage("terrain/flat/dirt-sw");
      one[5] = screen->getImage("terrain/flat/dirt-nw");

      two[0] = screen->getImage("terrain/flat/dirt-n-ne");
      two[1] = screen->getImage("terrain/flat/dirt-ne-se");
      two[2] = screen->getImage("terrain/flat/dirt-se-s");
      two[3] = screen->getImage("terrain/flat/dirt-s-sw");
      two[4] = screen->getImage("terrain/flat/dirt-sw-nw");
      two[5] = screen->getImage("terrain/flat/dirt-nw-n");

      three[0] = screen->getImage("terrain/flat/dirt-n-ne-se");
      three[1] = screen->getImage("terrain/flat/dirt-ne-se-s");
      three[2] = screen->getImage("terrain/flat/dirt-se-s-sw");
      three[3] = screen->getImage("terrain/flat/dirt-s-sw-nw");
      three[4] = screen->getImage("terrain/flat/dirt-sw-nw-n");
      three[5] = screen->getImage("terrain/flat/dirt-nw-n-ne");

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
   } else if (type == ADD_FLAT_SAVANNA) {
      one[0] = screen->getImage("terrain/flat/savanna-n");
      one[1] = screen->getImage("terrain/flat/savanna-ne");
      one[2] = screen->getImage("terrain/flat/savanna-se");
      one[3] = screen->getImage("terrain/flat/savanna-s");
      one[4] = screen->getImage("terrain/flat/savanna-sw");
      one[5] = screen->getImage("terrain/flat/savanna-nw");

      two[0] = screen->getImage("terrain/flat/savanna-n-ne");
      two[1] = screen->getImage("terrain/flat/savanna-ne-se");
      two[2] = screen->getImage("terrain/flat/savanna-se-s");
      two[3] = screen->getImage("terrain/flat/savanna-s-sw");
      two[4] = screen->getImage("terrain/flat/savanna-sw-nw");
      two[5] = screen->getImage("terrain/flat/savanna-nw-n");

      three[0] = screen->getImage("terrain/flat/savanna-n-ne-se");
      three[1] = screen->getImage("terrain/flat/savanna-ne-se-s");
      three[2] = screen->getImage("terrain/flat/savanna-se-s-sw");
      three[3] = screen->getImage("terrain/flat/savanna-s-sw-nw");
      three[4] = screen->getImage("terrain/flat/savanna-sw-nw-n");
      three[5] = screen->getImage("terrain/flat/savanna-nw-n-ne");

      *four = NULL;
   } else if (type == ADD_FLAT_SAVANNA_TO_WATER) {
      one[0] = screen->getImage("terrain/flat/savanna-to-water-n");
      one[1] = screen->getImage("terrain/flat/savanna-to-water-ne");
      one[2] = screen->getImage("terrain/flat/savanna-to-water-se");
      one[3] = screen->getImage("terrain/flat/savanna-to-water-s");
      one[4] = screen->getImage("terrain/flat/savanna-to-water-sw");
      one[5] = screen->getImage("terrain/flat/savanna-to-water-nw");

      two[0] = screen->getImage("terrain/flat/savanna-to-water-n-ne");
      two[1] = screen->getImage("terrain/flat/savanna-to-water-ne-se");
      two[2] = screen->getImage("terrain/flat/savanna-to-water-se-s");
      two[3] = screen->getImage("terrain/flat/savanna-to-water-s-sw");
      two[4] = screen->getImage("terrain/flat/savanna-to-water-sw-nw");
      two[5] = screen->getImage("terrain/flat/savanna-to-water-nw-n");

      three[0] = screen->getImage("terrain/flat/savanna-to-water-n-ne-se");
      three[1] = screen->getImage("terrain/flat/savanna-to-water-ne-se-s");
      three[2] = screen->getImage("terrain/flat/savanna-to-water-se-s-sw");
      three[3] = screen->getImage("terrain/flat/savanna-to-water-s-sw-nw");
      three[4] = screen->getImage("terrain/flat/savanna-to-water-sw-nw-n");
      three[5] = screen->getImage("terrain/flat/savanna-to-water-nw-n-ne");

      *four = NULL;
   } else if (type == ADD_FLAT_STONE_PATH) {
      one[0] = screen->getImage("terrain/flat/stone-path-n");
      one[1] = screen->getImage("terrain/flat/stone-path-ne");
      one[2] = screen->getImage("terrain/flat/stone-path-se");
      one[3] = screen->getImage("terrain/flat/stone-path-s");
      one[4] = screen->getImage("terrain/flat/stone-path-sw");
      one[5] = screen->getImage("terrain/flat/stone-path-nw");

      two[0] = screen->getImage("terrain/flat/stone-path-n-ne");
      two[1] = screen->getImage("terrain/flat/stone-path-ne-se");
      two[2] = screen->getImage("terrain/flat/stone-path-se-s");
      two[3] = screen->getImage("terrain/flat/stone-path-s-sw");
      two[4] = screen->getImage("terrain/flat/stone-path-sw-nw");
      two[5] = screen->getImage("terrain/flat/stone-path-nw-n");

      *three = NULL;
      *four = NULL;
   } else if (type == ADD_LAVA) {
      one[0] = screen->getImage("terrain/lava-n");
      one[1] = screen->getImage("terrain/lava-ne");
      one[2] = screen->getImage("terrain/lava-se");
      one[3] = screen->getImage("terrain/lava-s");
      one[4] = screen->getImage("terrain/lava-sw");
      one[5] = screen->getImage("terrain/lava-nw");

      two[0] = screen->getImage("terrain/lava-n-ne");
      two[1] = screen->getImage("terrain/lava-ne-se");
      two[2] = screen->getImage("terrain/lava-se-s");
      two[3] = screen->getImage("terrain/lava-s-sw");
      two[4] = screen->getImage("terrain/lava-sw-nw");
      two[5] = screen->getImage("terrain/lava-nw-n");

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
   } else if (type == ADD_WATER_COAST) {
      one[0] = screen->getImage("terrain/water/ford-n");
      one[1] = screen->getImage("terrain/water/ford-ne");
      one[2] = screen->getImage("terrain/water/ford-se");
      one[3] = screen->getImage("terrain/water/ford-s");
      one[4] = screen->getImage("terrain/water/ford-sw");
      one[5] = screen->getImage("terrain/water/ford-nw");

      *two = NULL;
      *three = NULL;
      *four = NULL;
   } else if (type == ADD_WATER_ICE) {
      one[0] = screen->getImage("terrain/water/ice-n");
      one[1] = screen->getImage("terrain/water/ice-ne");
      one[2] = screen->getImage("terrain/water/ice-se");
      one[3] = screen->getImage("terrain/water/ice-s");
      one[4] = screen->getImage("terrain/water/ice-sw");
      one[5] = screen->getImage("terrain/water/ice-nw");

      two[0] = screen->getImage("terrain/water/ice-n-ne");
      two[1] = screen->getImage("terrain/water/ice-ne-se");
      two[2] = screen->getImage("terrain/water/ice-se-s");
      two[3] = screen->getImage("terrain/water/ice-s-sw");
      two[4] = screen->getImage("terrain/water/ice-sw-nw");
      two[5] = screen->getImage("terrain/water/ice-nw-n");

      *three = NULL;
      *four = NULL;
   } else if (type == ADD_WATER_ICE_TO_WATER) {
      one[0] = screen->getImage("terrain/water/ice-to-water-n");
      one[1] = screen->getImage("terrain/water/ice-to-water-ne");
      one[2] = screen->getImage("terrain/water/ice-to-water-se");
      one[3] = screen->getImage("terrain/water/ice-to-water-s");
      one[4] = screen->getImage("terrain/water/ice-to-water-sw");
      one[5] = screen->getImage("terrain/water/ice-to-water-nw");

      two[0] = screen->getImage("terrain/water/ice-to-water-n-ne");
      two[1] = screen->getImage("terrain/water/ice-to-water-ne-se");
      two[2] = screen->getImage("terrain/water/ice-to-water-se-s");
      two[3] = screen->getImage("terrain/water/ice-to-water-s-sw");
      two[4] = screen->getImage("terrain/water/ice-to-water-sw-nw");
      two[5] = screen->getImage("terrain/water/ice-to-water-nw-n");

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
   while (!terrain[position] && position<6) position++;
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
   bool differentTerrain[6];
   bool needSoft = false; // Indicates if the cell needs to be soften

   initializeVariables(one, two, three, four, ADD_WATER_ICE_TO_WATER);
   for (int j=0; j<6; j++) differentTerrain[j] = false;
   /// @todo Initialize variables only when they are needed.
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

   ///delete [] terrain;
   terrain = new char[1];
   terrain[0] = WATER_OCEAN;
   softenTerrain(WATER_FORD, terrain, 1, ADD_WATER_FORD);

   /*delete [] terrain;
   terrain = new char[1];
   terrain[0] = WATER_FORD;
   softenTerrain(WATER_OCEAN, terrain, 1, ADD_WATER_OCEAN);*/

   delete [] terrain;
   terrain = new char[2];
   terrain[0] = WATER_FORD;
   terrain[1] = WATER_OCEAN;
   softenTerrain(WATER_COAST, terrain, 2, ADD_WATER_COAST);

   delete [] terrain;
   terrain = new char[3];
   terrain[0] = WATER_COAST;
   terrain[1] = WATER_FORD;
   terrain[2] = WATER_OCEAN;
   softenTerrain(WATER_ICE, terrain, 3, ADD_WATER_ICE);

   delete [] terrain;
   terrain = new char[3];
   terrain[0] = WATER_COAST;
   terrain[1] = WATER_FORD;
   terrain[2] = WATER_OCEAN;
   softenTerrain(WATER_ICE, terrain, 3, ADD_WATER_ICE_TO_WATER);

   delete [] terrain;
   terrain = new char[4];
   terrain[0] = WATER_COAST;
   terrain[1] = WATER_FORD;
   terrain[2] = WATER_ICE;
   terrain[3] = WATER_OCEAN;
   softenTerrain(DESERT_ROAD, terrain, 4, ADD_DESERT_ROAD);

   delete [] terrain;
   terrain = new char[5];
   terrain[0] = DESERT_ROAD;
   terrain[1] = WATER_COAST;
   terrain[2] = WATER_FORD;
   terrain[3] = WATER_ICE;
   terrain[4] = WATER_OCEAN;
   softenTerrain(DESERT, terrain, 5, ADD_DESERT);

   delete [] terrain;
   terrain = new char[6];
   terrain[0] = DESERT;
   terrain[1] = DESERT_ROAD;
   terrain[2] = FLAT_DIRT;
   terrain[3] = FLAT_ROAD;
   terrain[4] = FLAT_STONE_PATH;
   terrain[5] = WATER_ICE;
   softenTerrain(FLAT_SAVANNA, terrain, 6, ADD_FLAT_SAVANNA);

   delete [] terrain;
   terrain = new char[6];
   terrain[0] = DESERT;
   terrain[1] = DESERT_ROAD;
   terrain[2] = WATER_COAST;
   terrain[3] = WATER_FORD;
   terrain[4] = WATER_ICE;
   terrain[5] = WATER_OCEAN;
   softenTerrain(DESERT_SAND, terrain, 6, ADD_DESERT_SAND);

   delete [] terrain;
   terrain = new char[8];
   terrain[0] = DESERT;
   terrain[1] = DESERT_ROAD;
   terrain[2] = DESERT_SAND;
   terrain[3] = FLAT_DIRT;
   terrain[4] = FLAT_ROAD;
   terrain[5] = FLAT_SAVANNA;
   terrain[6] = FLAT_STONE_PATH;
   terrain[7] = WATER_ICE;
   softenTerrain(FLAT_GRASS, terrain, 8, ADD_FLAT_GRASS);

   delete [] terrain;
   terrain = new char[3];
   terrain[0] = WATER_COAST;
   terrain[1] = WATER_FORD;
   terrain[2] = WATER_OCEAN;
   softenTerrain(FLAT_GRASS, terrain, 3, ADD_FLAT_GRASS_TO_WATER);

   delete [] terrain;
   terrain = new char[4];
   terrain[0] = DESERT_SAND;
   terrain[1] = WATER_COAST;
   terrain[2] = WATER_FORD;
   terrain[3] = WATER_OCEAN;
   softenTerrain(FLAT_SAVANNA, terrain, 4, ADD_FLAT_SAVANNA_TO_WATER);

   delete [] terrain;
   terrain = new char[7];
   terrain[0] = DESERT;
   terrain[1] = DESERT_ROAD;
   terrain[2] = DESERT_SAND;
   terrain[3] = WATER_COAST;
   terrain[4] = WATER_FORD;
   terrain[5] = WATER_ICE;
   terrain[6] = WATER_OCEAN;
   softenTerrain(FLAT_ROAD, terrain, 7, ADD_FLAT_ROAD);

   delete [] terrain;
   terrain = new char[8];
   terrain[0] = DESERT;
   terrain[1] = DESERT_ROAD;
   terrain[2] = DESERT_SAND;
   terrain[3] = FLAT_DIRT;
   terrain[4] = WATER_COAST;
   terrain[5] = WATER_FORD;
   terrain[6] = WATER_ICE;
   terrain[7] = WATER_OCEAN;
   softenTerrain(FLAT_STONE_PATH, terrain, 8, ADD_FLAT_STONE_PATH);

   delete [] terrain;
   terrain = new char[8];
   terrain[0] = DESERT;
   terrain[1] = DESERT_ROAD;
   terrain[2] = DESERT_SAND;
   terrain[3] = FLAT_ROAD;
   terrain[4] = WATER_COAST;
   terrain[5] = WATER_FORD;
   terrain[6] = WATER_ICE;
   terrain[7] = WATER_OCEAN;
   softenTerrain(FLAT_DIRT, terrain, 8, ADD_FLAT_DIRT);

   delete [] terrain;
   terrain = new char[12];
   terrain[0] = DESERT;
   terrain[1] = DESERT_ROAD;
   terrain[2] = DESERT_SAND;
   terrain[3] = FLAT_DIRT;
   terrain[4] = FLAT_GRASS;
   terrain[5] = FLAT_ROAD;
   terrain[6] = FLAT_SAVANNA;
   terrain[7] = FLAT_STONE_PATH;
   terrain[8] = WATER_COAST;
   terrain[9] = WATER_FORD;
   terrain[10] = WATER_ICE;
   terrain[11] = WATER_OCEAN;
   softenTerrain(CAVE_FLOOR, terrain, 12, ADD_CAVE_FLOOR);

   delete [] terrain;
   terrain = new char[13];
   terrain[0] = CAVE_FLOOR;
   terrain[1] = DESERT;
   terrain[2] = DESERT_ROAD;
   terrain[3] = DESERT_SAND;
   terrain[4] = FLAT_DIRT;
   terrain[5] = FLAT_GRASS;
   terrain[6] = FLAT_ROAD;
   terrain[7] = FLAT_SAVANNA;
   terrain[8] = FLAT_STONE_PATH;
   terrain[9] = WATER_COAST;
   terrain[10] = WATER_FORD;
   terrain[11] = WATER_ICE;
   terrain[12] = WATER_OCEAN;
   softenTerrain(LAVA, terrain, 13, ADD_LAVA);

   delete [] terrain;
   terrain = new char[14];
   terrain[0] = CAVE_FLOOR;
   terrain[1] = DESERT;
   terrain[2] = DESERT_ROAD;
   terrain[3] = DESERT_SAND;
   terrain[4] = FLAT_DIRT;
   terrain[5] = FLAT_GRASS;
   terrain[6] = FLAT_ROAD;
   terrain[7] = FLAT_SAVANNA;
   terrain[8] = FLAT_STONE_PATH;
   terrain[9] = LAVA;
   terrain[10] = WATER_COAST;
   terrain[11] = WATER_FORD;
   terrain[12] = WATER_ICE;
   terrain[13] = WATER_OCEAN;
   softenTerrain(CAVE_HILLS, terrain, 14, ADD_CAVE_HILLS);

   delete [] terrain;
   terrain = new char[15];
   terrain[0] = CAVE_FLOOR;
   terrain[1] = CAVE_HILLS;
   terrain[2] = DESERT;
   terrain[3] = DESERT_ROAD;
   terrain[4] = DESERT_SAND;
   terrain[5] = FLAT_DIRT;
   terrain[6] = FLAT_GRASS;
   terrain[7] = FLAT_ROAD;
   terrain[8] = FLAT_SAVANNA;
   terrain[9] = FLAT_STONE_PATH;
   terrain[10] = LAVA;
   terrain[11] = WATER_COAST;
   terrain[12] = WATER_FORD;
   terrain[13] = WATER_ICE;
   terrain[14] = WATER_OCEAN;
   softenTerrain(DESERT_HILLS, terrain, 15, ADD_DESERT_HILLS);

   delete [] terrain;
   terrain = new char[16];
   terrain[0] = CAVE_FLOOR;
   terrain[1] = CAVE_HILLS;
   terrain[2] = DESERT;
   terrain[3] = DESERT_HILLS;
   terrain[4] = DESERT_ROAD;
   terrain[5] = DESERT_SAND;
   terrain[6] = FLAT_DIRT;
   terrain[7] = FLAT_GRASS;
   terrain[8] = FLAT_ROAD;
   terrain[9] = FLAT_SAVANNA;
   terrain[10] = FLAT_STONE_PATH;
   terrain[11] = LAVA;
   terrain[12] = WATER_COAST;
   terrain[13] = WATER_FORD;
   terrain[14] = WATER_ICE;
   terrain[15] = WATER_OCEAN;
   softenTerrain(DESERT_MOUNTAIN, terrain, 16, ADD_DESERT_MOUNTAIN);

   delete [] terrain;
}
