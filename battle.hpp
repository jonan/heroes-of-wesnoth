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
/// The battle class and a function to create battles.
/// @author Jonan

#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "map.hpp"

/// Max creatures for each team (not counting the hero
#define MAX_TEAM_UNITS 9
/// Max units in all the battle
#define MAX_BATTLE_UNITS 19
/// Agility needed to get a turn
#define TURN 10

class cell;
class hero;
class unit;

/// Controls all the aspects of a battle.
///
/// -no detailed description-
class battle : public map {
   private:
      hero *player;
      unit *creatures[MAX_TEAM_UNITS];
      int turns[MAX_BATTLE_UNITS];
      int turn;
      bool endBattle;

      // This function is executed in the main loop. If
      // it returns true, the loop ends, else it continues.
      bool frame(void);

      // Function to execute when the cell where the mouse is over is detected.
      void mouseOver(const int x, const int y, const int button);

      // Starts the next turn.
      void nextTurn(void);

      // Removes a unit from the battle and deletes it.
      void deleteCreature(unit &creature);

      // Controls the units not controled by the player.
      void ai(void);

   public:
      /// @param[in] player The player's hero.
      /// @param[in] enemies Array with all the enemies.
      /// @param[in] numberEnemies Number of enemies in the array.
      battle(hero &player, unit **enemies, const int numberEnemies); // Constructor
};

/// Creates and starts a battle.
///
/// -no detailed description-
void createBattle(void);
/// Creates and starts a battle.
///
/// -no detailed description-
void createFastBattle(hero &player, const int enemyType, const int terrainType);

#endif // BATTLE_HPP
