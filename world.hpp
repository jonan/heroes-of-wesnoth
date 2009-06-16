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
/// The World class.
/// @author Jonan

#ifndef WORLD_HPP
#define WORLD_HPP

#include <list>

#include "map.hpp"

class Hero;

/// Controls all the aspects of a world.
class World : public Map {
  public:
    /// @param[in] map_file File where the map is stored.
    World(const char *map_file); // Constructor
    ~World(void); // Destructor

    /// Puts a hero in the map.
    /// @param[in] hero Hero to put in the map.
    /// @param[in] x X coordinate of the hero's position.
    /// @param[in] y Y coordinate of the hero's position.
    void setHero(Hero &hero, const int x, const int y);

  private:
    // Function to execute when the user left clicks on a cell.
    virtual void mouseLeftClick(const int x, const int y);

    // Starts the next turn.
    virtual void nextTurn(void);

    // Removes a unit from the world and deletes it.
    void deleteCreature(Cell &position);

    // This function is executed in the main loop. If
    // it returns true, the loop ends, else it continues.
    virtual bool frame(void);

    std::list<Hero*> heroes;
    int number_enemies;
    bool end_world;

    DISALLOW_COPY_AND_ASSIGN(World);
};

#endif // WORLD_HPP
