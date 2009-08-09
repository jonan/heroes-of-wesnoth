/*
This file is part of Heroes of Wesnoth.
Copyright (C) 2007, 2008, 2009 Jon Ander Peñalba <jonan88@gmail.com>

Heroes of Wesnoth is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

Heroes of Wesnoth is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Heroes of Wesnoth. If not, see <http://www.gnu.org/licenses/>
*/

/// @file
/// The Map class.
/// @author Jonan

#ifndef MAP_HPP
#define MAP_HPP

#include "game_loop.hpp"
#include "util.hpp"

class Cell;
class Unit;
class UnitAnimation;

/// Controls all the attributes of a map.
/// Basically consist of lots of Cell classes working
/// together to create a map an to be able to use it.
/// (This class is meant to be inherit, not to be used directly)
class Map : public GameLoop {
  public:
    /// Starts the map.
    virtual void start(void);

  protected:
    // @{
    // Constructors
    Map(const int width, const int height);
    Map(const char *map_file);
    // @}
    virtual ~Map(void); // Destructor

    // Sets the terrain type to all the cells in the map.
    void setTerrainToAllCells(const char *id);

    // Loads the terrain, creatures and items of the map from a file.
    void loadMapFile(const char *file_name);

    // Adjusts the visible map to the window size.
    void adjustVisibleMap(void);

    // Makes the hole map visible.
    void makeMapVisible(void);

    // Returns a cell where the creature can attack.
    Cell* getAttackCell(void);

    // Updates the map according to the mouse state
    void updateMouse(void);
    // Function to execute when the mouse is over a cell.
    virtual void mouseOverCell(const int x, const int y);
    // Function to execute when the user left clicks on a cell.
    virtual void mouseLeftClick(const int x, const int y) {}
    // Function to execute when the user right clicks on a cell.
    virtual void mouseRightClick(const int x, const int y);

    // Starts the next turn.
    virtual void nextTurn(void) {}

    // Moves the selected creature to a cell.
    void move(Cell &cell);
    // Makes the selected creature attack the unit in the given cell.
    virtual void attack(Cell &cell) {}

    // Connects all the cells in the map.
    void connectCells(void);

    // Softens the map to make it look nicer.
    void smoothMap(void);

    // Centers the map view in a given cell
    void centerView(Cell& position);
    // Centers the map view in a given creature
    void centerView(Unit& creature);

    // Draws the map in the screen.
    virtual void draw(void);

    // This function is executed in the main loop. If
    // it returns true, the loop ends, else it continues.
    virtual bool frame(void) = 0;

    // @{
    // Functions to delete parts of the map.
    // This functions shouldn't normally be called (the
    // desctructor will call them), but they are usefull in some cases.
    void deleteCells     (void);
    void deleteCreatures (void);
    // @}

    int map_width, map_height; // The map's size.
    Cell **map;

    Unit *selected_unit; // The unit that's selected.
    UnitAnimation *animation;

    Cell *mouse_over_cell; // The cell where the mouse is.

  private:
    // Initialize all the variables.
    void init(void);

    // Adds the corresponding smooth images to the cell.
    void addSmoothImages(Cell *cell, bool *need_smooth, const char *terrain);

    Coordinates first_cell_coor; // Map coordinates of the top left visible cell.
    Coordinates first_cell_pos;  // Position of the top left visible cell in the screen.

    int window_width, window_height; // Size of the map's window
    int window_horizontal_cells, window_vertical_cells; // Number of visible cells

    DISALLOW_COPY_AND_ASSIGN(Map);
};

#endif // MAP_HPP
