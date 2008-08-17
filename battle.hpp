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
/// The Battle class and a function to create battles.
/// @author Jonan

#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "map.hpp"

class Hero;

/// Controls all the aspects of a battle.
///
/// -no detailed description-
class Battle : public Map {
  public:
    /// @param[in] player The player's hero.
    /// @param[in] enemies Array with all the enemies.
    /// @param[in] num_enemies Number of enemies in the array.
    /// @param[in] terrain Type of terrain.
    Battle(Hero &player, Unit **enemies, const int num_enemies, const int terrain); // Constructor
    /// @param[in] player The player's hero.
    /// @param[in] enemies The enemy's hero.
    /// @param[in] terrain Type of terrain.
    Battle(Hero &player, Hero &enemy, const int terrain); // Constructor

    /// Starts the battle.
    ///
    /// -no detailed description-
    virtual void start(void);

    /// Returns true if the battle was won.
    ///
    /// -no detailed description-
    ///
    /// @return true if the battle was won, false if it wasn't.
    bool win(void);

  private:
    static const int MAX_TEAM_UNITS = 9; // Not counting the hero.
    static const int MAX_BATTLE_UNITS = 20;
    static const int TURN = 10; // Agility needed to get a turn

    // Things to do no matter what constructor was called.
    void init(const int terrain);

    // This function is executed in the main loop. If
    // it returns true, the loop ends, else it continues.
    virtual bool frame(void);

    // Function to execute when the mouse is over a cell.
    virtual void mouseOverCell(const int x, const int y);
    // Function to execute when the user left clicks on a cell.
    virtual void mouseLeftClick(const int x, const int y);

    // Starts the next turn.
    virtual void nextTurn(void);

    // Deletes a creature.
    void deleteCreature(Unit &creature);

    // Controls the units not controled by the player.
    void ai(void);

    // Function to call whenever there is an animation.
    void animation(const int sprites);

    Hero *player, *enemy;
    Unit *enemy_creatures[MAX_TEAM_UNITS];
    int turns[MAX_BATTLE_UNITS];
    int turn;
    bool end_battle;

    DISALLOW_COPY_AND_ASSIGN(Battle);
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
/// @param[in] enemy_type Type of enemies to face.
/// @param[in] terrain_type Type of terrain where to fight.
/// @return true if the battle was won, false if it wasn't.
bool createBattle(Hero &player, const char enemy_type, const char terrain_type);
/// Creates and starts a battle.
///
/// -no detailed description-
///
/// @param[in] player The player's hero.
/// @param[in] enemy The enemy's hero.
/// @param[in] terrain_type Type of terrain where to fight.
/// @return true if the battle was won, false if it wasn't.
bool createBattle(Hero &player, Hero &enemy, const char terrain_type);

#endif // BATTLE_HPP
