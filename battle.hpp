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

/// @file
/// The battle class and a function to create battles.
/// @author Jonan

#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "hero.hpp"
#include "map.hpp"

/// Controls all the aspects of a battle.
///
/// -no detailed description-
class battle : public map {
   private:
      hero *player;
      unit *creature;

      // This function is executed in the main loop. If
      // it returns true, the loop ends, else it continues.
      bool frame(void);

   public:
      battle(void); // Constructor

      /// Starts the battle.
      ///
      /// -no detailed description-
      void start(void);
      /// Puts the enemy creatures in the map.
      ///
      /// -no detailed description-
      ///
      /// @param[in] creaturesArray An array with all the creatures.
      /// @param[in] number number of creatures in the array.
      void setCreatures(unit **creaturesArray, int number);
};

/// Creates and starts a battle.
///
/// -no detailed description-
void createBattle(void);

#endif // BATTLE_HPP
