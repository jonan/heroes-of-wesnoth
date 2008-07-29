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
/// The hero class.
/// @author Jonan

#ifndef HERO_HPP
#define HERO_HPP

#include "unit.hpp"

#include "macros.hpp"

/// Types of heros
enum {FIGHTER = '0', WIZARD};

/// Types of AI
enum {HUMAN, COMPUTER};

/// Stores the hero's atributes.
///
/// -no detailed description-
class Hero : public Unit {
  public:
    /// @param[in] type Type of hero.
    /// @param[in] ai Type of AI.
    Hero(const int type, const int ai); // Constructor
    ~Hero(void); // Destructor

    /// Returns the hero's type of AI.
    ///
    /// -no detailed description-
    ///
    /// @return The hero's type of AI
    int getAI(void) {return ai;}
    /// Returns the hero's visibility.
    ///
    /// -no detailed description-
    ///
    /// @return The hero's visibility
    int getVisibility(void) {return visibility;}
    /// Returns a creature controled by the hero.
    ///
    /// -no detailed description-
    ///
    /// @param[in] number Number of the creature to return.
    /// @return A creature controled by the hero.
    Unit* getCreature(const int number) {return creature[number];}

    /// Assings a new creature to the hero.
    ///
    /// If the hero can't control a new creature (he already
    /// controls 9) returns false, else returns true.
    ///
    /// @param[in] creature The new unit the hero can control.
    /// @return If the recruitment was successful or not.
    bool recruitCreature(Unit *creature);
    /// Assings a new creature to the hero.
    ///
    /// -no detailed description-
    ///
    /// @param[in] creature The new unit the hero can control.
    /// @param[in] position Position were the unit should be.
    /// @return The unit that was in that position.
    Unit* recruitCreature(Unit *creature, const int position);

    /// Draws the hero in the given position.
    ///
    /// -no detailed description-
    ///
    /// @param[in] position The position where the hero should be drawn.
    virtual void draw(SDL_Rect &position);

  private:
    static const int MAX_UNITS = 9;

    // Sets the heros attributes acording to his type.
    // (Implemented in hero_type.cpp)
    virtual void setCreaturesAttributes(void);

    int ai; // Type of Artificial Intelligence
    int visibility; // How far the hero sees

    Unit *creature[MAX_UNITS]; // The creatures a hero can control

    DISALLOW_COPY_AND_ASSIGN(Hero);
};

#endif // HERO_HPP
