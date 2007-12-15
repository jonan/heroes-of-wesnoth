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

#ifndef MAP_HPP
#define MAP_HPP

#include <string.h>

#include "unit.hpp"

/// The six relative positions to a cell
#define N  0
#define NE 1
#define SE 2
#define S  3
#define SW 4
#define NW 5

/// Cells of the map.
///
/// An class to control all the independent
/// cells in any type of map.
class cell {
   private:
      SDL_Rect position; // Position where to draw the cell
      SDL_Surface *terrain; // Surface of the terrain
      unit *creature; // Creature in the cell
      cell *connectedCell[6]; // The six cells that are next to it

      bool mouseOver; // Indicates if the mouse is over the cell or not
      bool selected; // Indicates if the unit in that cell is selected
      bool canMove; // Indicates if the selected creature can move to this cell

      // Calculates to what cells can a creature move.
      void creatureMovement(const int movement);
      // Erases previos calculations about a creatures movement.
      void eraseMovement(const int movement);

   public:
      cell(void); // Constructor
      /// @param [in] position Position where to draw the cell
      /// @param [in] terrain Surface of the terrain
      /// @param [in] creature Creature in the cell
      cell(SDL_Rect position, SDL_Surface *terrain = NULL, unit *creature = NULL); // Constructor

      /// Sets the cell's position.
      ///
      /// -no detailed description-
      ///
      /// @param [in] position Position where to draw the cell
      void setPosition(SDL_Rect position);
      /// Sets the cell's terrain.
      ///
      /// -no detailed description-
      ///
      /// @param [in] terrain Surface of the terrain
      void setTerrain(SDL_Surface *imageName);
      /// Puts a creature in the cell.
      ///
      /// -no detailed description-
      ///
      /// @param [in] creature Creature to put in the cell
      void setCreature(unit *creature);
      /// Returns the creature in the cell.
      ///
      /// -no detailed description-
      ///
      /// @return Pointer to the unit in the cell.
      unit *getCreature(void);
      /// Returns the cell's position.
      ///
      /// -no detailed description-
      ///
      /// @return Cell's position
      SDL_Rect getPosition(void);
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
      /// -no detailed description-
      cell* select(void);
      /// The cell is no longer selected.
      ///
      /// -no detailed description-
      void unselect(void);

      /// Connects a cell to this one.
      ///
      /// Indicates which are the cells next to this one
      /// in any direction (N, NE, SE, S, SW or NW).
      ///
      /// @param [in] position Relative position of the cell (N, NE, SE, S, SW or NW).
      /// @param [in] connectedCell The cell to conect.
      void connectCell(const int position, cell* connectedCell);

      /// Draws the cell in the screen.
      ///
      /// -no detailed description-
      ///
      /// @param[in] screen -no detailed description-
      void draw(graphics *screen);

      /// Indicates if the selected creature can move to this cell.
      ///
      /// -no detailed description-
      ///
      /// @return true if the selected creature can move to this cell, false if not.
      bool canMoveHere(void);
};

/// Controls all the attributes of a map.
///
/// Basically consist of lots of cell classes working
/// together to create a map an to be able to use it.
class map {
   private:
      int sizeX, sizeY; // The map's size
      SDL_Surface *terrainBase; // The most used terrain in the map
      cell **battleMap;
      cell *selectedCell; // The cell that's selected
      cell *mouseOverCell; // The cell where the mouse is

      // Connects all the cells in the map
      void connectCells(void);

   public:
      /// @param [in] sizeX
      /// @param [in] sizeY
      map(const int sizeX = 18, const int sizeY = 9); // Constructor
      ~map(void); // Destructor

      /// Indicates the terrain image of the map.
      ///
      /// -no detailed description-
      ///
      /// @param[in] terrainImgName Name of the terrain's image, without the "img/" or the ".png".
      /// @param[in] screen -no detailed description-
      void setTerrain(const char *terrainImgName, graphics *screen);
      /// Puts the hero in the map.
      ///
      /// -no detailed description-
      ///
      /// @param [in] player The player's hero.
      void setHero(unit *player);

      /// Tells the map the mouse's position.
      ///
      /// Every time the mouse's position or the mouse's buttons
      /// change, this function should be called.
      ///
      /// @param[in] x The x coordinate of the mouse's position
      /// @param[in] y The y coordinate of the mouse's position
      /// @param[in] pressed If the mouse left button is pressed or not
      void moveMouse(int x, int y, int pressed);

      /// Draws the map in the screen.
      ///
      /// -no detailed description-
      ///
      /// @param[in] screen -no detailed description-
      void draw(graphics *screen);
};

#endif

/* Last Version: Jonan */
