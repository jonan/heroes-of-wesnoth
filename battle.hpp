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
      unit **creatures;
      int numberCreatures; // Number of enemy creatures
      int totalUnits; // Total number of units in the battle
      int *turns;

      // This function is executed in the main loop. If
      // it returns true, the loop ends, else it continues.
      bool frame(void);
      // Returns the creatura that has the next turn.
      unit* nextTurn(void);
      // Puts the enemy creatures in the map.
      void setCreatures(unit **creaturesArray, int number);
      // Function to execute when the cell where the mouse is over is detected.
      void mouseOver(int x, int y, int button);

   public:
      battle(hero *player, unit **enemies, int numberEnemies); // Constructor

      /// Starts the battle.
      ///
      /// -no detailed description-
      void start(void);
};

/// Creates and starts a battle.
///
/// -no detailed description-
void createBattle(void);

#endif // BATTLE_HPP
