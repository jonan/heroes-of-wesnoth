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
/// The Cell class.
/// @author Jonan

#ifndef CELL_HPP
#define CELL_HPP

#include <deque>
#include <string>

#include <SDL/SDL.h>

#include "macros.hpp"

class Unit;

struct Coordinates;
struct SpecialImage;

/// The six relative positions to a cell
enum {N, NE, SE, S, SW, NW};

/// Parts of the drawing of a cell
enum {DRAW_TERRAIN, DRAW_SPECIAL_IMG, DRAW_UNIT};

/// Class to control all each independent cell in a map.
class Cell {
  public:
    Cell(void);  // Constructor
    ~Cell(void); // Destructor

    // @{
    /// Set functions.
    void setAlpha       (SDL_Surface &alpha)        {this->alpha = &alpha;     }
    void setStars       (SDL_Surface &stars)        {this->stars = &stars;     }
    void setPassable    (const bool passable)       {this->passable = passable;}
    void setTerrain     (const char *id);
    void setCreature    (Unit *creature);
    void setItem        (const char *id);
    void setCoordinates (const int x, const int y);
    // @}

    // @{
    /// Get functions.
    const char* getTerrainType   (void)                        {return type.c_str();         }
    const char* getItemType      (void)                        {return item.c_str();         }
    Unit*       getCreature      (void)                        {return creature;             }
    Cell*       getConnectedCell (const int place)             {return connected_cell[place];}
    void        getCoordinates   (int &x, int &y);
    void        getPath          (int* &path, int &movements);
    // @}

    /// Adds an image to the cell's terrain.
    /// @param[in] terrain Surface of the terrain.
    void addImage(SDL_Surface &terrain);
    /// Adds a special image to the cell's terrain.
    /// @param[in] terrain Surface of the terrain.
    void addSpecialImage(SDL_Surface &terrain);

    // @{
    /// Indicates if the mouse is in the cell or not
    void putMouse    (void) {mouse_over = true; }
    void removeMouse (void) {mouse_over = false;}
    // @}

    /// Indicates that the cell is now selected.
    /// The cell is selected and the cells where
    /// the unit can move are marked.
    void select(void);
    /// The cell is no longer selected.
    /// Marks the cell as not being selected and tells all the cells
    /// where the unit could move that now it can not move there.
    void unselect(void);

    /// Calculates which cells are visible.
    /// @param[in] visibility Visibility of the hero on the cell.
    void calculateView(int visibility);

    /// Connects a cell to this one.
    /// Indicates which are the cells next to this one
    /// in any direction (N, NE, SE, S, SW or NW).
    /// @param[in] position Relative position of the cell (N, NE, SE, S, SW or NW).
    /// @param[in] connected_cell The cell to conect.
    void connectCell(const int position, Cell* connected_cell);

    /// Draws the cell in the screen.
    /// @param[in] position Position where to draw the cell.
    /// @param[in] part Part of the cell to draw.
    void draw(SDL_Rect position, const int part);

    // @{
    /// Indicates if an action can be performed.
    bool canMoveHere   (void) {return can_move;  }
    bool canAttackHere (void) {return can_attack;}
    // @}

  private:
    // Calculates to what cells can a creature move.
    void calculateMovement(const int creature_movement, int *path, const int movements);
    // Erases previos calculations about a creatures movement.
    void eraseMovement(void);

    std::string type; // Type of terrain of the cell
    std::deque<SDL_Surface*> terrain_images; // Surfaces of the terrain
    SpecialImage *special_images;
    SDL_Surface *stars, *alpha;

    Unit *creature;
    std::string item;

    Cell *connected_cell[6]; // The six cells that are next to this one
    Coordinates *map_position; // Map coordinates of the cell

    int *path; // Path to follow in a units movement
    int movements; // Number of cells to go through to follow the path
    bool passable; // Indicates if a unit can move to this cell

    bool mouse_over; // Indicates if the mouse is over the cell
    bool selected;   // Indicates if the unit in the cell is selected

    bool can_move;   // Indicates if the selected creature can move to this cell
    bool can_attack; // Indicates if the unit in the cell can be attacked

    bool visible;    // Indicates if the cell is visible or not

    DISALLOW_COPY_AND_ASSIGN(Cell);
};

#endif // CELL_HPP
