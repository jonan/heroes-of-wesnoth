/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007-2008 Jon Ander Peñalba <jonan88@gmail.com>

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
/// The World class.
/// @author Jonan

#ifndef WORLD_HPP
#define WORLD_HPP

#include <deque>

#include "map.hpp"

class Hero;

/// Controls all the aspects of a world.
///
/// -no detailed description-
class World : public Map {
  public:
    /// @param[in] map_file File where the map is stored.
    /// @param[in] width Map's width.
    /// @param[in] height Map's height 
    World(const char *map_file, const int width, const int height); // Constructor
    ~World(void); // Destructor

    /// Puts a hero in the map.
    ///
    /// -no detailed description-
    ///
    /// @param[in] player Hero to put in the map.
    /// @param[in] x X coordinate of the hero's position.
    /// @param[in] y Y coordinate of the hero's position.
    void setHero(Hero &player, const int x, const int y);

  private:
    // This function is executed in the main loop. If
    // it returns true, the loop ends, else it continues.
    virtual bool frame(void);

    // Function to execute when the user left clicks on a cell.
    virtual void mouseLeftClick(const int x, const int y);

    // Starts the next turn.
    virtual void nextTurn(void);

    // Puts the enemies in the map.
    void setEnemies(const char *map_file);
    // Puts the items on the map.
    void setItems(const char *map_file);
    // Removes a unit from the world and deletes it.
    void deleteCreature(Cell &position);

    std::deque<Hero*> players;
    int turn;
    int number_enemies;
    bool end_world;

    DISALLOW_COPY_AND_ASSIGN(World);
};

#endif // WORLD_HPP
