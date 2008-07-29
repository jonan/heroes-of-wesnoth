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

#include "macros.hpp"

/// Types of terrain.
enum {CAVE_FLOOR = '0',
      CAVE_HILLS,
      DESERT,
      DESERT_HILLS,
      DESERT_MOUNTAIN,
      DESERT_ROAD,
      DESERT_SAND,
      FLAT_DIRT,
      FLAT_GRASS,
      FLAT_ROAD,
      FLAT_SAVANNA = 'a',
      FLAT_STONE_PATH,
      HILLS,
      LAVA,
      WATER_COAST,
      WATER_FORD,
      WATER_ICE,
      WATER_OCEAN,
      WATER_SNOW,
      WATER_SNOW_HILLS,
      LAST_TERRAIN = WATER_SNOW_HILLS};

// Struct to store coordinates.
struct Coordinates {
  int x;
  int y;
};

class Cell;
class Unit;

/// Controls all the attributes of a map.
///
/// Basically consist of lots of cell classes working
/// together to create a map an to be able to use it.
/// (This class is meant to be inherit, not to be used directly)
class Map {
  public:
    /// Starts the map.
    ///
    /// -no detailed description-
    virtual void start(void);

    /// Indicates the terrain image of a cell.
    ///
    /// If both coordinates are -1 applies
    /// the terrain to all the cells in the map.
    ///
    /// @param[in] terrain_name Type of terrain.
    /// @param[in] x X coordinate of the cell.
    /// @param[in] y Y coordinate of the cell.
    // (Implemented in map_terrain.cpp)
    void setTerrain(const char terrain_name, const int x, const int y);

  protected:
    Map(const int width, const int height); // Constructor
    virtual ~Map(void); // Destructor

    // Returns a cell where the creature can attack.
    Cell* getAttackCell(void);

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
    void moveCreature(Cell &endPosition);

    // Connects all the cells in the map.
    void connectCells(void);
    // Softens the map to make it look nicer.
    // (Implemented in map_smooth.cpp)
    void softenMap(void);

    // Draws the map in the screen.
    virtual void draw(void);

    int width, height; // The map's size.
    Cell **battle_map;
    Unit *selected_unit; // The unit that's selected.
    Cell *mouse_over_cell; // The cell where the mouse is.

  private:
    // Softens a type of terrain.
    // (Implemented in map_smooth.cpp)
    void softenTerrain(const char cell_terrain, char *terrain, const int number_terrains, const int soft_images);

    Coordinates first_cell_coor; // Map coordinates of the top left visible cell.
    Coordinates first_cell_pos; // Position of the top left visible cell in the screen.
    int horizontal_cells, vertical_cells; // Number of visible cells

    DISALLOW_COPY_AND_ASSIGN(Map);
};

#endif // MAP_HPP
