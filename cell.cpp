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
#include "unit.hpp"

// class cell

// Calculates to what cells can a creature move.
void cell::creatureMovement(const int movement, int *path, const int movements) {
   if (movementPenalty != 1000) { // A creature can move here
      if (path == NULL) { // It's the first call to this funtion so the creature is over this cell.
         for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
            if (connectedCell[i]) {
               int *tempPath = new int[1];
               tempPath[0] = i;
               connectedCell[i]->creatureMovement(movement, tempPath, 1);
            }
         }
      } else if (movement>0) {
         if (creature==NULL) {
            if (this->path == NULL || this->movements > movements) { // Need to change path
               canMove = true;
               if (this->path != NULL) delete [] this->path;
               this->path = path;
               this->movements = movements;
               for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
                  if (connectedCell[i]) {
                     int *tempPath = new int[this->movements+1];
                     for (int j=0; j<(this->movements); j++)
                        tempPath[j] = this->path[j];
                     tempPath[this->movements] = i;
                     connectedCell[i]->creatureMovement(movement-movementPenalty, tempPath, movements+1);
                  }
               }
            }
         } else {
            canAttack = true;
            if (this->path == NULL || this->movements > movements-1) { // Need to change path
               if (this->path != NULL) delete [] this->path;
               this->movements = movements-1;
               this->path = new int[this->movements];
               for (int i=0; i<(this->movements); i++)
                  this->path[i] = path[i];
               delete [] path;
            }
         }
      } else if (creature != NULL) {
         canAttack = true;
         if (this->path == NULL || this->movements > movements-1) {
            if (this->path != NULL) delete [] this->path;
            this->movements = movements-1;
            this->path = new int[this->movements];
            for (int i=0; i<(this->movements); i++)
               this->path[i] = path[i];
            delete [] path;
         }
      } else delete [] path;
   } else delete [] path;
}

// Erases previos calculations about a creatures movement.
void cell::eraseMovement(const int movement, const int call) {
   if (movementPenalty != 1000) { // A creature can move here
      if (call == 0) { // It's the first call to this funtion so the creature is over this cell.
         movements = 0;
         canAttack = false;
         canMove = false;
         for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
            if (connectedCell[i])
               connectedCell[i]->eraseMovement(movement);
         }
      } else if (path != NULL) {
         delete [] path;
         path = NULL;
         movements = 0;
         canAttack = false;
         canMove = false;
         for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
            if (connectedCell[i])
               connectedCell[i]->eraseMovement(movement-1);
         }
      }
   }
}

// Constructor
cell::cell(void) {
   creature = NULL;
   path = NULL;

   mouseOver = false;
   selected = false;
   canMove = false;
   canAttack = false;
   visible = false;
}

// Destructor
cell::~cell(void) {
   if (path) delete [] path;
}

// Sets the cell's terrain.
void cell::addImage(SDL_Surface &terrain, const char type) {
   if (type != -1) {
      // If a new type is assigned, it means the new surface is
      // the main one, so all previous ones need to be deleted.
      if (!this->terrain.empty()) this->terrain.clear();
      this->type = type;
   }
   this->terrain.push_back(&terrain);
}

// Puts a creature in the cell.
void cell::setCreature(unit *creature) {
   this->creature = creature;
   if (creature) creature->setPosition(*this);
}

// Sets the cells map coordinates.
void cell::setCoordinates(const int x, const int y) {
   mapX = x;
   mapY = y;
}

// Returns the cells map coordinates.
void cell::getCoordinates(int &x, int &y) {
   x = mapX;
   y = mapY;
}

// Returns the path that the unit has to follow to
// reach this cell and how many movements are needed.
void cell::getPath(int* &path, int &movements) {
   path = this->path;
   movements = this->movements;
}

// The cell is selected and the cell where
// the unit can move are marked.
void cell::select(void) {
   if (creature!=NULL) {
      selected = true;
      creatureMovement(creature->getMovement(), NULL, 0);
   }
}

// Marks the cell as not being selected and tells all the cells
// where the unit could move that now it can not move there.
void cell::unselect(int movement) {
   if (movement == -1) movement = creature->getMovement();
   selected = false;
   eraseMovement(movement, 0);
}

// Calculates which cells are visible.
void cell::calculateView(int visibility) {
   if (visibility > 0) {
      visible = true;
      for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
         if (connectedCell[i])
            connectedCell[i]->calculateView(visibility-1);
      }
   }
}

// Indicates which are the cells next to this one
// in any direction (N, NE, SE, S, SW or NW).
void cell::connectCell(const int position, cell* connectedCell){
   this->connectedCell[position] = connectedCell;
}

// Draws the cell in the screen.
void cell::draw(SDL_Rect position) {
   if (visible) {
      for (unsigned int i=0; i<terrain.size(); i++)
         screen->draw(terrain[i], position);
      if (mouseOver) screen->draw(alpha, position);
      if (canMove) screen->draw(alpha, position);
      if (creature) creature->draw(position);
      if (selected) screen->draw(alpha, position);
   } else screen->draw(stars, position);
}
