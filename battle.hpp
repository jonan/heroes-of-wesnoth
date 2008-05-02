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
#define MAX_CREATURES 9
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
      unit *creatures[MAX_CREATURES];
      int turns[MAX_BATTLE_UNITS];
      int turn;
      bool endBattle;

      // Puts the enemy creatures in the map.
      void setCreatures(void);

      // Function to execute when the cell where the mouse is over is detected.
      void mouseOver(const int x, const int y, const int button);
      // This function is executed in the main loop. If
      // it returns true, the loop ends, else it continues.
      bool frame(void);

      // Returns the next unit.
      unit* nextTurn(void);
      // Function to call when a turn ends.
      void finishTurn(void);

      // Moves the selected creature to a given cell.
      void moveCreature(cell *endPosition);
      // Removes a unit from the battle.
      void removeCreature(unit &creature);

      // Controls the units not controled by the player.
      void ai(void);

   public:
      /// @param[in] player The player's hero.
      /// @param[in] enemies Array with all the enemies.
      /// @param[in] numberEnemies Number of enemies in the array.
      battle(hero &player, unit **enemies, int numberEnemies); // Constructor

      /// Starts the battle.
      ///
      /// -no detailed description-
      void start(void);
      //void results(hero &player, unit &enemies);
};

/// Creates and starts a battle.
///
/// -no detailed description-
void createBattle(void);

#endif // BATTLE_HPP
