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

/// @file
/// The cell class.
/// @author Jonan

#ifndef CELL_HPP
#define CELL_HPP

#include <deque>

#include <SDL/SDL.h>

using namespace std;

class unit;

/// The six relative positions to a cell
#define N  0
#define NE 1
#define SE 2
#define S  3
#define SW 4
#define NW 5

/// Cells of the map.
///
/// A class to control all the independent
/// cells in any type of map.
class cell {
   private:
      deque<SDL_Surface*> terrain; // Surfaces of the terrain
      SDL_Surface *stars, *alpha;
      char type; // Type of terrain of the cell
      unit *creature; // Creature in the cell
      cell *connectedCell[6]; // The six cells that are next to it
      int mapX, mapY; // Map coordinates of the cell
      int *path; // Path to follow in a units movement
      int movements; // Number of cells to go through to follow the path
      int movementPenalty; // Amount of movement needed to go throw this cell

      bool mouseOver; // Indicates if the mouse is over the cell or not
      bool selected; // Indicates if the unit in the cell is selected
      bool canMove; // Indicates if the selected creature can move to this cell
      bool canAttack; // Indicates if the unit in the cell can be attacked
      bool visible; // Indicates if the cell is visible or not

      // Calculates to what cells can a creature move.
      void creatureMovement(const int movement, int *path, const int movements);
      // Erases previos calculations about a creatures movement.
      void eraseMovement(const int movement, const int call = 1);

   public:
      cell(void); // Constructor
      ~cell(void); // Destructor

      /// Adds an image to the cell's terrain.
      ///
      /// -no detailed description-
      ///
      /// @param[in] terrain Surface of the terrain.
      /// @param[in] type Type of terrain.
      void addImage(SDL_Surface &terrain, const char type = -1);
      /// Sets the image used to outstand a cell.
      ///
      /// -no detailed description-
      ///
      /// @param[in] alpha Alpha surface.
      void setAlpha(SDL_Surface &alpha);
      /// Sets the image to show when the cell is not visible.
      ///
      /// -no detailed description-
      ///
      /// @param[in] stars Surface of the stars.
      void setStars(SDL_Surface &stars);
      /// Puts a creature in the cell.
      ///
      /// -no detailed description-
      ///
      /// @param[in] creature Creature to put in the cell.
      void setCreature(unit *creature);
      /// Sets the movement penalty for the cell.
      ///
      /// If penalty is 1000 a creature
      /// can never be over this cell.
      ///
      /// @param[in] penalty Movement penalty for this cell.
      void setMovementPenalty(const int penalty);
      /// Sets the cells map coordinates.
      ///
      /// -no detailed description-
      ///
      /// @param[in] x X coordinate in the map.
      /// @param[in] y Y coordinate in the map.
      void setCoordinates(const int x, const int y);

      /// Returns the cell's terrain.
      ///
      /// -no detailed description-
      ///
      /// @return Type of terrain of the cell.
      char getTerrain(void);
      /// Returns the creature in the cell.
      ///
      /// -no detailed description-
      ///
      /// @return Pointer to the unit in the cell.
      unit* getCreature(void);
      /// Returns the cells map coordinates.
      ///
      /// -no detailed description-
      ///
      /// @param[out] x X coordinate in the map.
      /// @param[out] y Y coordinate in the map.
      void getCoordinates(int &x, int &y);
      /// Returns one of the six connected cells.
      ///
      /// -no detailed description-
      ///
      /// @param[in] place Can be N, NE, SE, S, SW or NW.
      /// @return The connected cell.
      cell* getConnectedCell(const int place);
      /// Returns the information needed to move a unit.
      ///
      /// Returns the path that the unit has to follow to
      /// reach this cell and how many movements are needed.
      ///
      /// @param[out] path The path that the unit has to follow.
      /// @param[out] movements Movements needed to get to the cell.
      void getPath(int* &path, int &movements);

      /// Indicates that the mouse is over the cell.
      ///
      /// -no detailed description-
      void putMouse(void);
      /// The mouse is no longer over the cell.
      ///
      /// -no detailed description-
      void removeMouse(void);

      /// Indicates that the cell is now selected.
      ///
      /// The cell is selected and the cell where
      /// the unit can move are marked.
      ///
      /// @return If everything was correct, this, else NULL.
      void select(void);
      /// The cell is no longer selected.
      ///
      /// Marks the cell as not being selected and tells all the cells
      /// where the unit could move that now it can not move there.
      /// (To use when the creature has been erased but you know the movement)
      ///
      /// @param[in] movement Movement of the creature (only needed if the unit isn't over the cell).
      void unselect(int movement = -1);

      /// Calculates which cells are visible.
      ///
      /// -no detailed description-
      ///
      /// @param[in] visibility Visibility of the hero on the cell.
      void calculateView(int visibility);

      /// Connects a cell to this one.
      ///
      /// Indicates which are the cells next to this one
      /// in any direction (N, NE, SE, S, SW or NW).
      ///
      /// @param[in] position Relative position of the cell (N, NE, SE, S, SW or NW).
      /// @param[in] connectedCell The cell to conect.
      void connectCell(const int position, cell* connectedCell);

      /// Draws the cell in the screen.
      ///
      /// -no detailed description-
      void draw(SDL_Rect position);

      /// Indicates if the selected creature can move to this cell.
      ///
      /// -no detailed description-
      ///
      /// @return true if the selected creature can move to this cell, false if not.
      bool canMoveHere(void);
      /// Indicates if the selected creature can attack the unit in this cell.
      ///
      /// -no detailed description-
      ///
      /// @return true if the selected creature can attack the unit in this cell, false if not.
      bool canAttackHere(void);
};

#endif // CELL_HPP
