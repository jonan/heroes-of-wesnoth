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
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

/// @file
/// All the different missions that can be created.
/// @author Jonan

#ifndef MISSION_HPP
#define MISSION_HPP

#include "macros.hpp"

class Hero;
class World;

/// Represents a scenario.
class Mission {
  public:
    /// @param[in] map The name of the map to use in the mission.
    /// @param[in] number_allies The number of units each of the heroes allies has.
    /// @param[in] width The width of the map.
    /// @param[in] height The height of the map.
    /// @param[in] hero_position_x Starting position of the hero - x-coordinate.
    /// @param[in] hero_position_y Starting position of the hero - y-coordinate.
    Mission(const char *map, const int number_allies,
            const int width, const int height,
            const int hero_position_x, const int hero_position_y); // Constructor
    ~Mission(); // Destructor

    /// Launches the mission.
    void startMission();

  private:
    World *war;
    Hero *player;
    int hero_position_x;
    int hero_position_y;
    int number_allies;

    DISALLOW_COPY_AND_ASSIGN(Mission);
};

// @{
/// Create and start a mission.
void mission1(void);
void mission2(void);
void mission3(void);
// @}

#endif // MISSION_HPP
