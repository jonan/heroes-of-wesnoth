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
   terrain = NULL;
   creature = NULL;
   for (int i=0; i<6; i++) {
      connectedCell[i] = NULL;
   }
   mouseOver = false;
   selected = false;
   canMove = false;
   canAttack = false;
}

// Sets the cell's position.
void cell::setPosition(SDL_Rect position) {
   this->position = position;
}

// Sets the cell's terrain.
void cell::setTerrain(SDL_Surface &terrain) {
   this->terrain = &terrain;
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

// Returns the cell's position.
SDL_Rect cell::getPosition(void) {
   return position;
}

// Returns the creature in the cell.
unit* cell::getCreature(void) {
   return creature;
}

// Returns the cells map coordinates.
void cell::getCoordinates(int &x, int &y) {
   x = mapX;
   y = mapY;
}

// Returns one of the six connected cells.
cell* cell::getConnectedCell(const int place) {
   return connectedCell[place];
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
   /// @todo Make sure returning this is needed.
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
   /// @todo Look if the creature is still on the cell when it's unselected.
   selected = false;
   eraseMovement( creature->getMovement()+1 );
}

// Indicates which are the cells next to this one
// in any direction (N, NE, SE, S, SW or NW).
void cell::connectCell(const int position, cell* connectedCell){
   /// @todo Maybe change the param *cell to &cell (future plan)
   this->connectedCell[position] = connectedCell;
}

// Draws the cell in the screen.
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
