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
along with Heroes of Wesnoth. If not, see <http://www.gnu.org/licenses/>
*/

/// @file
/// The Hero class.
/// @author Jonan

#ifndef HERO_HPP
#define HERO_HPP

#include "unit.hpp"

/// Types of heros
enum {ELF = '0' , HUMAN, UNDEAD};

/// Stores the hero's attributes.
class Hero : public Unit {
  public:
    /// @param[in] type Type of hero.
    Hero(const int type); // Constructor
    ~Hero(void); // Destructor

    // @{
    /// Get functions.
    Unit* getCreature   (const int number) {return creature[number];}
    int   getVisibility (void)             {return visibility;      }
    // @}

    /// Assings a new creature to the hero.
    /// @param[in] creature The new unit the hero can control.
    /// @param[in] position Position were the unit should be.
    void recruitCreature(Unit *creature, const int position = -1);

    /// Draws the hero in the given position.
    /// @param[in] position The position where the hero should be drawn.
    virtual void draw(SDL_Rect &position) {drawUnit(position);}

  private:
    static const int MAX_UNITS = 9;

    Unit *creature[MAX_UNITS]; // The creatures a hero controls

    int visibility; // How far the hero sees

    DISALLOW_COPY_AND_ASSIGN(Hero);
};

#endif // HERO_HPP
