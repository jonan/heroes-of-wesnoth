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
#include "events.hpp"
#include "graphics.hpp"
#include "map.hpp"
#include "timer.hpp"
#include "unit.hpp"

// Constructor
map::map(const int width, const int height) {
   this->width = width;
   this->height = height;

   // Create the array of cells
   battleMap = new cell*[width];
   for (int i=0; i<width; i++)
      battleMap[i] = new cell[height];

   connectCells();

   for (int x=0; x<width; x++)
      for (int y=0; y<height; y++)
         battleMap[x][y].setCoordinates(x, y);

   firstCell.x = 0;
   firstCell.y = 0;

   selectedUnit=NULL;
   mouseOverCell=NULL;
}

// Destructor
map::~map(void) {
   for (int i=0; i<width; i++)
      delete [] battleMap[i];
   delete [] battleMap;
}

// Returns a cell where the creature can attack.
cell* map::getAttackCell(void) {
   /// @todo Optimize this function.
   cell *temp = NULL;
   int x, y;

   x=0;
   y=0;

   while (!temp && x<width) {
      if (battleMap[x][y].canAttackHere() && battleMap[x][y].getCreature()->getMaster() != NULL)
         temp = &battleMap[x][y];
      else {
         y++;
         if (y == height) {
            y=0;
            x++;
         }
      }
   }

   return temp;
}

// Tells the map the mouse's position.
void map::moveMouse(const int x, const int y, const int button) {
   int i=firstCell.x, j=firstCell.y;
   SDL_Rect cellPosition;

   cellPosition.x=17;
   if ( (firstCell.x%2)==1 ) cellPosition.y = 77;
   else cellPosition.y = 41;

   if (mouseOverCell)
      mouseOverCell->removeMouse();

   // Find out which cell is the mouse over
   while (x > cellPosition.x){
      cellPosition.x += 54;
      i++;
   }
   i--;
   if (i>=firstCell.x && i<18+firstCell.x) {
      if ( (i%2)==1 ) cellPosition.y = 77;
      else cellPosition.y = 41;
      while (y > cellPosition.y){
         cellPosition.y += 72;
         j++;
      }
      j--;
      if (j>=firstCell.y && j<9+firstCell.y) { // battleMap[i][j] is a valid cell and the mouse is over it
         battleMap[i][j].putMouse();
         mouseOverCell = &battleMap[i][j];
         if (button == BUTTON_LEFT) mouseClick(i, j);
      }
   }
   // move visible map
   if ( (i<firstCell.x || keys[SDLK_LEFT]) && firstCell.x!=0)
      firstCell.x--;
   else if ( (i>firstCell.x+17 || keys[SDLK_RIGHT]) && firstCell.x!=width-18)
      firstCell.x++;
   if ( (j<firstCell.y || keys[SDLK_UP]) && firstCell.y!=0)
      firstCell.y--;
   else if ( (j>firstCell.y+8 || keys[SDLK_DOWN]) && firstCell.y!=height-9)
      firstCell.y++;
}

// Moves a creature to a cell.
void map::moveCreature(cell &endPosition) {
   int *path;
   int movements;
   cell *actualPosition;
   cell *temp;
   int actualX, actualY; // Coordinates of the actual cell
   int endX, endY; // Coordinates of the cell where to move

   actualPosition = selectedUnit->getPosition();

   actualPosition->getCoordinates(actualX, actualY);
   endPosition.getCoordinates(endX, endY);

   endPosition.getPath(path, movements);
   /// @note This isn't too elegant
   for (int i=0; i<movements; i++) {
      // Make the creature face the same direction as moving
      if (path[i] == NE || path[i] == SE) selectedUnit->setFacingSide(RIGHT);
      else if (path[i] == NW || path[i] == SW) selectedUnit->setFacingSide(LEFT);

      selectedUnit->getPosition()->setCreature(NULL);
      temp = selectedUnit->getPosition()->getConnectedCell(path[i]);
      temp->setCreature(selectedUnit);
      selectedUnit->setPosition(*temp);
      draw();
      screen->update();
      screen->wait(100);
   }

   actualPosition->unselect(selectedUnit->getMovement());
}

// Connects all the cells in the map.
void map::connectCells(void) {
   for (int coor1=0; coor1<width; coor1++) {
      for (int coor2=0; coor2<height; coor2++) {
         if ( (coor1%2)==1 ) { // coor1 is an odd number
            if (coor1 == width-1) { // The last colum of the map
               if (coor2 == 0) {
                  battleMap[coor1][coor2].connectCell(N, NULL);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2+1]);
               } else if (coor2 == height-1) {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, NULL);
                  battleMap[coor1][coor2].connectCell(SW, NULL);
               } else {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2+1]);
               }
               battleMap[coor1][coor2].connectCell(NE, NULL);
               battleMap[coor1][coor2].connectCell(SE, NULL);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2]);
            } else if (coor2 == 0) { // The first row of the map
               battleMap[coor1][coor2].connectCell(N, NULL);
               battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
               battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2]);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2+1]);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2]);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2+1]);
            } else if (coor2 == height-1) { // Last row of the map
               battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
               battleMap[coor1][coor2].connectCell(S, NULL);
               battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2]);
               battleMap[coor1][coor2].connectCell(SE, NULL);
               battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2]);
               battleMap[coor1][coor2].connectCell(SW, NULL);
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
                  battleMap[coor1][coor2].connectCell(N, NULL);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(NE, NULL);
               } else if (coor2 == height-1) {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, NULL);
                  battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2-1]);
               } else {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(NE, &battleMap[coor1+1][coor2-1]);
               }
               battleMap[coor1][coor2].connectCell(NW, NULL);
               battleMap[coor1][coor2].connectCell(SW, NULL);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2]);
            } else if (coor1 == width-1) { // The last colum of the map
               if (coor2 == 0) {
                  battleMap[coor1][coor2].connectCell(N, NULL);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(NW, NULL);
               } else if (coor2 == height-1) {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, NULL);
                  battleMap[coor1][coor2].connectCell(NW,&battleMap[coor1-1][coor2-1]);
               } else {
                  battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(NW, &battleMap[coor1-1][coor2-1]);
               }
               battleMap[coor1][coor2].connectCell(NE, NULL);
               battleMap[coor1][coor2].connectCell(SE, NULL);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2]);
            } else if (coor2 == 0) { // The first row of the map
               battleMap[coor1][coor2].connectCell(N, NULL);
               battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
               battleMap[coor1][coor2].connectCell(NE, NULL);
               battleMap[coor1][coor2].connectCell(SE, &battleMap[coor1+1][coor2]);
               battleMap[coor1][coor2].connectCell(NW, NULL);
               battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2]);
            } else if (coor2 == height-1) { // Last row of the map
               battleMap[coor1][coor2].connectCell(N, &battleMap[coor1][coor2-1]);
               battleMap[coor1][coor2].connectCell(S, NULL);
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

// Draws the map in the screen.
void map::draw(void) {
   SDL_Rect position;

   // Position of the firts cell (top-left)
   position.x = 17;
   if ( (firstCell.x%2)==1 ) position.y = 77;
   else position.y = 41;
   position.w = 72;
   position.h = 72;

   screen->erase();
   // Draws the visible cells.
   for (int x=firstCell.x; x<18+firstCell.x; x++) {
      for (int y=firstCell.y; y<9+firstCell.y; y++) {
         battleMap[x][y].draw(position);
         position.y+=72;
      }
      if ( (x%2)==1 ) position.y=41; // x is an odd number
      else position.y=77;
      position.x+=54;
   }
}

// Starts the map.
void map::start(void) {
   // Set first turn.
   nextTurn();

   /// @todo Use the loop function in loop.hpp
   bool done = false;
   timer fps;

   while (!done) {
      fps.start();
      input->readInput();
      done = frame();
      screen->update();
      fps.end(30);
   }
}
