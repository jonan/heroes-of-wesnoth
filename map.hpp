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
      SDL_Surface *terrain; // Type of terrain
      unit *creature; // Creature in the cell
      cell *conectedCell[6]; // The six cells that are next to it

      bool mouseOver; // Indicates if the mouse is over the cell or not
      bool selected; // Indicates if the unit in that cell is selected

   public:
      cell(void); // Constructor
      //~cell(void); // Destructor

      void setPos(SDL_Rect position);
      void setTerrain(SDL_Surface *imageName);
      void setCreature(unit *creature);

      SDL_Rect getPos(void);
      unit *getCreature(void);

      /// Draws the cell in the screen.
      ///
      /// If the creature in the cell is selected, returns the
      /// movement, else returns 0
      ///
      /// @param[in] screen -no detailed description-
      int draw(graphics *screen);

      //void putMouse();
      //void removeMouse();
      //void select();
      //void unselect();
};

/// Controls all the attributes of a map.
///
/// Basically consist of lots of cell classes working
/// together to create a map an to be able to use it.
class map {
   private:
      SDL_Surface *terrainBase; // The most used terrain in the map
      cell battleMap[18][9];
      cell *selectedCell;

   public:
      map(void); // Constructor

      /// @param[in] terrainImgName Name of the terrain's image
      /// @param[in] screen -no detailed description-
      void setTerrain(const char terrainImgName[20], graphics *screen);
      void setHero(unit *player);

      /// Draws the map in the screen.
      ///
      /// -no detailed description-
      ///
      /// @param[in] screen -no detailed description-
      void draw(graphics *screen);

      //void selectMove(int x, int y, int move, graphics *screen);
      //void mousePos(int x, int y, int button, graphics *screen);
};

#endif

/* Last Version: Jonan */
