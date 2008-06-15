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
/// The world class and a function to create worlds.
/// @author Jonan

#ifndef WORLD_HPP
#define WORLD_HPP

#include <deque>

#include "map.hpp"

using namespace std;

class hero;

/// Controls all the aspects of a world.
///
/// -no detailed description-
class world : public map {
   private:
      deque<hero*> players;
      int turn;
      int numberEnemies;
      bool endWorld;

      // This function is executed in the main loop. If
      // it returns true, the loop ends, else it continues.
      bool frame(void);

      // Function to execute when the user clicks on a cell.
      void mouseClick(const int x, const int y);

      // Starts the next turn.
      void nextTurn(void);

      // Puts the enemies in the map.
      void setEnemies(const char *mapFile);
      // Removes a unit from the world and deletes it.
      void deleteCreature(cell &position);

   public:
      /// @param[in] mapFile File where the map is stored.
      /// @param[in] width Map's width.
      /// @param[in] height Map's height 
      world(const char *mapFile, const int width, const int height); // Constructor
      /// Puts a hero in the map.
      ///
      /// -no detailed description-
      ///
      /// @param[in] player Hero to put in the map.
      /// @param[in] x X coordinate of the hero's position.
      /// @param[in] y Y coordinate of the hero's position.
      void setHero(hero &player, const int x, const int y);
};

#endif // WORLD_HPP
