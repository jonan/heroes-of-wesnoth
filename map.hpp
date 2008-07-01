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
/// The map class.
/// @author Jonan

#ifndef MAP_HPP
#define MAP_HPP

// @{
/// Types of terrain.
#define CAVE_FLOOR   '0'
#define DESERT       '1'
#define FLAT_GRASS   '2'
#define FLAT_ROAD    '3'
#define FORD         '4'
#define WATER_COAST  '5'
#define WATER_ICE    '6'
#define WATER_OCEAN  '7'
#define LAST_TERRAIN '7'
// @}

class cell;
class unit;

// Struct to store the coordinates of a cell.
struct cellCoor {
   int x;
   int y;
};

/// Controls all the attributes of a map.
///
/// Basically consist of lots of cell classes working
/// together to create a map an to be able to use it.
/// (This class is meant to be inherit, not to be used directly)
class map {
   private:
      cellCoor firstCell; // Coordinates of the top left cell.
      int horizontalCells, verticalCells; // Number of visible cells

      // Softens a type of terrain.
      // (Implemented in map_smooth.cpp)
      void softenTerrain(const char cellTerrain, char *terrain, const int numberTerrains, const int softImages);

   protected:
      int width, height; // The map's size.
      cell **battleMap;
      unit *selectedUnit; // The unit that's selected.
      cell *mouseOverCell; // The cell where the mouse is.

      map(const int width, const int height); // Constructor
      virtual ~map(void); // Destructor

      // Returns a cell where the creature can attack.
      cell* getAttackCell(void);

      // Tells the map the mouse's position.
      void moveMouse(const int x, const int y, const int button);
      // Function to execute when the user clicks on a cell.
      virtual void mouseClick(const int x, const int y) = 0;

      // Starts the next turn.
      virtual void nextTurn(void) = 0;

      // This function is executed in the main loop. If
      // it returns true, the loop ends, else it continues.
      virtual bool frame(void) = 0;

      // Moves a creature to a cell.
      void moveCreature(cell &endPosition);

      // Connects all the cells in the map.
      void connectCells(void);
      // Softens the map to make it look nicer.
      // (Implemented in map_smooth.cpp)
      void softenMap(void);

      // Draws the map in the screen.
      virtual void draw(void);

   public:
      /// Starts the map.
      ///
      /// -no detailed description-
      virtual void start(void);

      /// Indicates the terrain image of a cell.
      ///
      /// Specify only the terrainName attribute to
      /// apply the terrain to all the cells of the map.
      ///
      /// @param[in] terrainName Type of terrain.
      /// @param[in] x X coordinate of the cell.
      /// @param[in] y Y coordinate of the cell.
      // (Implemented in map_terrain.cpp)
      void setTerrain(const char terrainName, const int x = -1, const int y = -1);
};

#endif // MAP_HPP
