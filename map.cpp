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

#include "cell.hpp"
#include "graphics.hpp"
#include "hero.hpp"
#include "map.hpp"
#include "unit.hpp"

// Connects all the cells in the map.
void map::connectCells(void) {
   for (int coor1=0; coor1<sizeX; coor1++) {
      for (int coor2=0; coor2<sizeY; coor2++) {
         if ( (coor1%2)==1 ) { // coor1 is an odd number
            if (coor1 == sizeX-1) { // The last colum of the map
               if (coor2 == 0) {
                  //battleMap[coor1][coor2].connectCell(N, NULL);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2+1]);
               } else if (coor2 == sizeY-1) {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  //battleMap[coor1][coor2].connectCell(S, NULL);
                  //battleMap[coor1][coor2].connectCell(SW, NULL);
               } else {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2+1]);
               }
               //battleMap[coor1][coor2].connectCell(NE, NULL);
               //battleMap[coor1][coor2].connectCell(SE, NULL);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2]);
            } else if (coor2 == 0) { // The first row of the map
               //battleMap[coor1][coor2].connectCell(N, NULL);
               battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
               battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2]);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2+1]);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2]);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2+1]);
            } else if (coor2 == sizeY-1) { // Last row of the map
               battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
               //battleMap[coor1][coor2].connectCell(S, NULL);
               battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2]);
               //battleMap[coor1][coor2].connectCell(SE, NULL);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2]);
               //battleMap[coor1][coor2].connectCell(SW, NULL);
            } else {
               battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
               battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
               battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2]);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2+1]);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2]);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2+1]);
            }
         } else { // coor1 is an even number
            if (coor1 == 0) { // The first colum of the map
               if (coor2 == 0) {
                  //battleMap[coor1][coor2].connectCell(N, NULL);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  //battleMap[coor1][coor2].connectCell(NE, NULL);
               } else if (coor2 == sizeY-1) {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  //battleMap[coor1][coor2].connectCell(S, NULL);
                  battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2-1]);
               } else {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2-1]);
               }
               //battleMap[coor1][coor2].connectCell(NW, NULL);
               //battleMap[coor1][coor2].connectCell(SW, NULL);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2]);
            } else if (coor1 == sizeX-1) { // The last colum of the map
               if (coor2 == 0) {
                  //battleMap[coor1][coor2].connectCell(N, NULL);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  //battleMap[coor1][coor2].connectCell(NW, NULL);
               } else if (coor2 == sizeY-1) {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  //battleMap[coor1][coor2].connectCell(S, NULL);
                  battleMap[coor1][coor2].connectCell(NW,&battleMap[coor1-1][coor2-1]);
               } else {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2-1]);
               }
               //battleMap[coor1][coor2].connectCell(NE, NULL);
               //battleMap[coor1][coor2].connectCell(SE, NULL);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2]);
            } else if (coor2 == 0) { // The first row of the map
               //battleMap[coor1][coor2].connectCell(N, NULL);
               battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
               //battleMap[coor1][coor2].connectCell(NE, NULL);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2]);
               //battleMap[coor1][coor2].connectCell(NW, NULL);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2]);
            } else if (coor2 == sizeY-1) { // Last row of the map
               battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
               //battleMap[coor1][coor2].connectCell(S, NULL);
               battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2-1]);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2]);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2-1]);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2]);
            } else {
               battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
               battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
               battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2-1]);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2]);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2-1]);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2]);
            }
         }
      }
   }
}

// Moves a unit to a cell.
void map::moveUnit(unit &creature, int* &path, const int movements) {
   cell *temp;

   /// @note This isn't too elegant
   for (int i=0; i<movements; i++) {
      creature.getPosition()->setCreature(NULL);
      temp = creature.getPosition()->getConnectedCell(path[i]);
      temp->setCreature(&creature);
      creature.setPosition(*temp);
      draw();
      screen->update();
      screen->wait(100);
   }
}

// Returns a cell where the creature can attack.
cell* map::getAttackCell(void) {
   cell *temp = NULL;
   int x, y;

   x=0;
   y=0;

   while (!temp && x<sizeX) {
      if (battleMap[x][y].canAttackHere() && battleMap[x][y].getCreature()->getMaster() != NULL)
         temp = &battleMap[x][y];
      else {
         y++;
         if (y == sizeY) {
            y=0;
            x++;
         }
      }
   }

   return temp;
}

// Constructor
map::map(const int sizeX, const int sizeY) {
   SDL_Rect terrainPos;

   // Position of the firts cell (top-left)
   terrainPos.x = 17;
   terrainPos.y = 41;
   terrainPos.w = 72;
   terrainPos.h = 72;

   this->sizeX = sizeX;
   this->sizeY = sizeY;

   battleMap = new cell*[sizeX];
   for (int i=0; i<sizeX; i++)
      battleMap[i] = new cell[sizeY];

   // For creating a battle map grid
   // Top Left     -       0,       0
   // Top Right    - sizeX-1,       0
   // Bottom Left  -       0, sizeY-1
   // Bottom Right - sizeX-1, sizeY-1
   for (int x=0; x<sizeX; x++) {
      for (int y=0; y<sizeY; y++) {
         battleMap[x][y].setPosition(terrainPos);
         battleMap[x][y].setCoordinates(x, y);
         terrainPos.y+=72;
      }
      if ( (x%2)==1 ) {terrainPos.y=41;} // x is an odd number
      else {terrainPos.y=77;}
      terrainPos.x+=54;
   }

   connectCells();
   selectedUnit=NULL;
   mouseOverCell=NULL;
}

// Destructor
map::~map(void) {
   for (int i=0; i<sizeX; i++)
      delete [] battleMap[i];
   delete [] battleMap;
}

// Puts the hero in the map.
void map::setHero(hero &player) {
   battleMap[0][4].setCreature(&player);
   for (int i=0; i<9; i++)
      battleMap[1][i].setCreature(player.getCreature(i));
}

// Every time the mouse's position or the mouse's buttons
// change, this function should be called.
void map::moveMouse(const int x, const int y, const int button) {
   int i=0, j=0;
   SDL_Rect cellPosition = battleMap[i][j].getPosition();

   if (mouseOverCell)
      mouseOverCell->removeMouse();

   // Find out which cell is the mouse over
   while (x > cellPosition.x){
      cellPosition.x += 54;
      i++;
   }
   i--;
   if (i>=0 && i<sizeX) {
      cellPosition = battleMap[i][j].getPosition();
      while (y > cellPosition.y){
         cellPosition.y += 72;
         j++;
      }
      j--;
      if (j>=0 && j<sizeY) { // battleMap[i][j] is a valid cell and the mouse is over it
         battleMap[i][j].putMouse();
         mouseOverCell = &battleMap[i][j];
         mouseOver(i, j, button);
      }
   }
}

// Draws the map in the screen.
void map::draw(void) {
   for (int x=0; x<sizeX; x++) {
      for (int y=0; y<sizeY; y++) {
         battleMap[x][y].draw();
      }
   }
}
