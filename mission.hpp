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
/// All the different missions that can be created.
/// @author Jonan

#ifndef MISSION_HPP
#define MISSION_HPP

#include "world.hpp"

/// Represents a scenario.
///
/// -no detailed description-
class Mission {

   private:
      world *war;
      hero *player;
      int heroPositionX;
      int heroPositionY;
      int numberAllies;
   public:
      /// Constructor for mission objects.
      ///
      /// @param[in] *map The name of the map to use in the mission.
      /// @param[in] width The width of the map.
      /// @param[in] height The height of the map.
      /// @param[in] heroPositionX Starting position of the hero - x-coordinate.
      /// @param[in] heroPositionY Starting position of the hero - y-coordinate.
      /// @param[in] numberAllies The number of units each of the heroes allies has.
      Mission( const char *map, const int width,
               const int height, const int heroPositionX,
               const int heroPositionY, const int numberAllies );
      ~Mission();

      /// Launches the mission.
      ///
      /// -no detailed description-
      void startMission();
};

/// Creates and starts mission 1.
///
/// -no detailed description-
void mission1(void);
/// Creates and starts mission 2.
///
/// -no detailed description-
void mission2(void);
/// Creates and starts mission 3.
///
/// -no detailed description-
void mission3(void);

#endif // MISSION_HPP
