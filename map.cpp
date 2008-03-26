/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007  Jon Ander Peñalba <jonan88@gmail.com>

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

#include "graphics.hpp"
#include "map.hpp"
#include "unit.hpp"

// class cell

// Calculates to what cells can a creature move.
void cell::creatureMovement(const int movement, int call) {
   if (call == 1) { // It's the first call to this funtion so the creature is over this cell.
      for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
            if (connectedCell[i])
               connectedCell[i]->creatureMovement(movement);
      }
   } else if (movement>0) {
      if (creature==NULL) {
         canMove = true;
         for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
            if (connectedCell[i])
               connectedCell[i]->creatureMovement(movement-1);
         }
      } else canAttack = true;
   } else if (movement == 0 && creature!=NULL) canAttack = true;
}

// Erases previos calculations about a creatures movement.
void cell::eraseMovement(const int movement) {
   canAttack = false;
   if (movement>0) {
      canMove = false;
      for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
            if (connectedCell[i])
               connectedCell[i]->eraseMovement(movement-1);
      }
   }
}

// Constructor
cell::cell(void) {
   creature = NULL;
   mouseOver = false;
   selected = false;
   canMove = false;
   canAttack = false;
   for (int i=0; i<6; i++) {
      connectedCell[i] = NULL;
   }
}

// Sets the cell's position.
void cell::setPosition(SDL_Rect position) {
   this->position = position;
}

// Sets the cell's terrain.
void cell::setTerrain(SDL_Surface *terrain) {
   this->terrain = terrain;
}

// Puts a creature in the cell.
void cell::setCreature(unit *creature) {
   this->creature = creature;
   if (creature) creature->setPosition(*this);
}

// Sets the cells map coordinates.
void cell::setCoordinates(int x, int y) {
   mapX = x;
   mapY = y;
}

// Returns the creature in the cell.
unit* cell::getCreature(void) {
   return creature;
}

// Returns the cell's position.
SDL_Rect cell::getPosition(void) {
   return position;
}

// Returns the cells map coordinates.
void cell::getCoordinates(int &x, int &y) {
   x = mapX;
   y = mapY;
}

// Indicates that the mouse is over the cell.
void cell::putMouse(void) {
   mouseOver = true;
}

// The mouse is no longer over the cell.
void cell::removeMouse(void) {
   mouseOver = false;
}

// The cell is selected and the cell where
// the unit can move are marked.
cell* cell::select(void) {
   if (creature!=NULL) {
      selected = true;
      creatureMovement(creature->getMovement(), 1 );
      return this;
   } else
      return NULL;
}

// Marks the cell as not being selected and tells all the cells
// where the unit could move that now it can not move there.
void cell::unselect(void) {
   selected = false;
   eraseMovement( creature->getMovement()+1 );
}

// Indicates which are the cells next to this one
// in any direction (N, NE, SE, S, SW or NW).
void cell::connectCell(const int position, cell* connectedCell){
   this->connectedCell[position] = connectedCell;
}

// If the creature in the cell is selected, returns the
// movement, else returns 0
void cell::draw(void) {
   screen->draw(terrain, position);
   if (mouseOver) screen->draw("alpha", position);
   if (canMove) screen->draw("alpha", position);
   if (canAttack && mouseOver) {screen->draw("alpha", position);screen->draw("alpha", position);screen->draw("alpha", position);}
   if (creature) creature->draw(position);
   if (selected) screen->draw("alpha", position);
}

// Indicates if the selected creature can move to this cell.
bool cell::canMoveHere(void) {
   return canMove;
}

// Indicates if the selected creature can attack the unit in this cell.
bool cell::canAttackHere(void) {
   return canAttack;
}

// Puts the cell's unit to NULL and frees the memory assigned to
// the unit. It should be called when the unit's number is 0.
void cell::killCreature(void) {
   delete creature;
   creature = NULL;
}

// ---End---

// class map

// connects all the cells in the map.
void map::connectCells(void) {
   for (int coor1=0; coor1<sizeX; coor1++) {
      for (int coor2=0; coor2<sizeY; coor2++) {
         if ( (coor1%2)==1 ) { // coor1 is an odd number
            if (coor1 == sizeX-1) { // The last colum of the map
               if (coor2 == 0) {
                  battleMap[coor1][coor2].connectCell(N, NULL);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(SW, &battleMap[coor1-1][coor2+1]);
               } else if (coor2 == sizeY-1) {
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
            } else if (coor2 == sizeY-1) { // Last row of the map
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
               } else if (coor2 == sizeY-1) {
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
            } else if (coor1 == sizeX-1) { // The last colum of the map
               if (coor2 == 0) {
                  battleMap[coor1][coor2].connectCell(N, NULL);
                  battleMap[coor1][coor2].connectCell(S, &battleMap[coor1][coor2+1]);
                  battleMap[coor1][coor2].connectCell(NW, NULL);
               } else if (coor2 == sizeY-1) {
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
            } else if (coor2 == sizeY-1) { // Last row of the map
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
         battleMap[x][y].setCreature(NULL);
         battleMap[x][y].setCoordinates(x, y);
         terrainPos.y+=72;
      }
      if ( (x%2)==1 ) {terrainPos.y=41;} // x is an odd number
      else {terrainPos.y=77;}
      terrainPos.x+=54;
   }

   connectCells();
   selectedCell=NULL;
   mouseOverCell=NULL;
}

// Destructor
map::~map(void) {
   for (int i=0; i<sizeX; i++)
      delete [] battleMap[i];
   delete [] battleMap;
}

// Indicates the terrain image of the map.
void map::setTerrain(const char *terrainImgName) {
   terrainBase = screen->getImage(terrainImgName);

   for (int x=0; x<sizeX; x++)
      for (int y=0; y<sizeY; y++) {
         battleMap[x][y].setTerrain(terrainBase);
      }
}

// Puts the hero in the map.
void map::setHero(unit *player) {
   battleMap[0][4].setCreature(player);
}

// Every time the mouse's position or the mouse's buttons
// change, this function should be called.
void map::moveMouse(int x, int y, int button) {
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

// ---End---
