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

#define FLOOR          0
#define GRASS_TO_WATER 1

// Sets the images needed to soften the map.
void initializeVariables(SDL_Surface **one, SDL_Surface **two,
                         SDL_Surface **three, SDL_Surface **four,
                         int type
                        ) {
   if (type == FLOOR) {
      one[0] = screen->getImage("floor-n");
      one[1] = screen->getImage("floor-ne");
      one[2] = screen->getImage("floor-se");
      one[3] = screen->getImage("floor-s");
      one[4] = screen->getImage("floor-sw");
      one[5] = screen->getImage("floor-nw");

      two[0] = screen->getImage("floor-n-ne");
      two[1] = screen->getImage("floor-ne-se");
      two[2] = screen->getImage("floor-se-s");
      two[3] = screen->getImage("floor-s-sw");
      two[4] = screen->getImage("floor-sw-nw");
      two[5] = screen->getImage("floor-nw-n");

      *three = NULL;
      *four = NULL;
   }else if (type == GRASS_TO_WATER) {
      one[0] = screen->getImage("grass-to-water-n");
      one[1] = screen->getImage("grass-to-water-ne");
      one[2] = screen->getImage("grass-to-water-se");
      one[3] = screen->getImage("grass-to-water-s");
      one[4] = screen->getImage("grass-to-water-sw");
      one[5] = screen->getImage("grass-to-water-nw");

      two[0] = screen->getImage("grass-to-water-n-ne");
      two[1] = screen->getImage("grass-to-water-ne-se");
      two[2] = screen->getImage("grass-to-water-se-s");
      two[3] = screen->getImage("grass-to-water-s-sw");
      two[4] = screen->getImage("grass-to-water-sw-nw");
      two[5] = screen->getImage("grass-to-water-nw-n");

      three[0] = screen->getImage("grass-to-water-n-ne-se");
      three[1] = screen->getImage("grass-to-water-ne-se-s");
      three[2] = screen->getImage("grass-to-water-se-s-sw");
      three[3] = screen->getImage("grass-to-water-s-sw-nw");
      three[4] = screen->getImage("grass-to-water-sw-nw-n");
      three[5] = screen->getImage("grass-to-water-nw-n-ne");

      four[0] = screen->getImage("grass-to-water-n-ne-se-s");
      four[1] = screen->getImage("grass-to-water-ne-se-s-sw");
      four[2] = screen->getImage("grass-to-water-se-s-sw-nw");
      four[3] = screen->getImage("grass-to-water-s-sw-nw-n");
      four[4] = screen->getImage("grass-to-water-sw-nw-n-ne");
      four[5] = screen->getImage("grass-to-water-nw-n-ne-se");
   }
}

// Adds the necesary images to soften the map.
void addImages(bool *terrain, cell &mapCell, SDL_Surface **one, SDL_Surface **two, SDL_Surface **three, SDL_Surface **four) {
   int position = 0;
   while (!terrain[position]) position++;
   while (position<7) {
      terrain[position] = false;
      if (position!=0 || !terrain[NW]) {
         if (terrain[position+1]) {
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
      } else {
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
      }
      while (!terrain[position] && position<7) position++;
   }
}

// Softens the map to make it look nicer.
void map::softenMap(void) {
   SDL_Surface *one[6];
   SDL_Surface *two[6];
   SDL_Surface *three[6];
   SDL_Surface *four[6];
   bool differentTerrain[7];
   cell *temp;

   initializeVariables(one, two, three, four, FLOOR);
   for (int j=0; j<7; j++) differentTerrain[j] = false;

   for (int x=0; x<width; x++) {
      for (int y=0; y<height; y++) {
         if (battleMap[x][y].getTerrain() != FLOOR) {
            for (int i=N; i<=NW; i++) {
               temp = battleMap[x][y].getConnectedCell(i);
               if (temp != NULL) {
                  if(temp->getTerrain() == FLOOR) differentTerrain[i] = true;
               }
            }
            addImages(differentTerrain, battleMap[x][y], one, two, three, four);
         }
      }
   }

   initializeVariables(one, two, three, four, GRASS_TO_WATER);
   for (int j=0; j<7; j++) differentTerrain[j] = false;

   for (int x=0; x<width; x++) {
      for (int y=0; y<height; y++) {
         if (battleMap[x][y].getTerrain() == WATER) {
            for (int i=N; i<=NW; i++) {
               temp = battleMap[x][y].getConnectedCell(i);
               if (temp != NULL) {
                  if(temp->getTerrain() == GRASS) differentTerrain[i] = true;
               }
            }
            addImages(differentTerrain, battleMap[x][y], one, two, three, four);
         }
      }
   }
}
