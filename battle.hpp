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

/// Max creatures for each team (not counting the hero)
#define MAX_TEAM_UNITS 9
/// Max units in all the battle
#define MAX_BATTLE_UNITS 19
/// Agility needed to get a turn
#define TURN 10
/// Max sprites in an animation
#define MAX_ANIMATION_SPRITES 10

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

      // Function to execute when the user clicks on a cell.
      void mouseClick(const int x, const int y);

      // Starts the next turn.
      void nextTurn(void);

      // Deletes a creature.
      void deleteCreature(unit &creature);

      // Controls the units not controled by the player.
      void ai(void);

      // Function to call whenever there is an animation.
      void animation(void);

   public:
      /// @param[in] player The player's hero.
      /// @param[in] enemies Array with all the enemies.
      /// @param[in] numberEnemies Number of enemies in the array.
      battle(hero &player, unit **enemies, const int numberEnemies); // Constructor

      /// Starts the battle.
      ///
      /// -no detailed description-
      void start(void);

      /// Returns true if the battle was won.
      ///
      /// -no detailed description-
      ///
      /// @return true if the battle was won, false if it wasn't.
      bool win(void);
};

/// Creates and starts the default.
///
/// -no detailed description-
void createDefaultBattle(void);
/// Creates and starts a battle.
///
/// -no detailed description-
///
/// @param[in] player The player's hero.
/// @param[in] enemyType Type of enemies to face.
/// @param[in] terrainType Type of terrain where to fight.
/// @return true if the battle was won, false if it wasn't.
bool createBattle(hero &player, const char enemyType, const char terrainType);

#endif // BATTLE_HPP
