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

#ifndef HERO_HPP
#define HERO_HPP

#include "unit.hpp"

#define MAX_UNITS 9

/// Stores the hero's atributes.
///
/// -no detailed description-
class hero : public unit{
   private:
      unit *creature[MAX_UNITS]; // The nine creatures a hero can control
      int numCreatures; // The number of creatures that the hero actualy controls

   public:
      /// @param[in] type Type of hero.
      hero(const char *type); // Constructor

      /// Assings a new creature to the hero.
      ///
      /// If the hero can't control a new creature (he already
      /// controls 9) returns false, else returns true.
      ///
      /// @param[in] creature The new unit the hero can control.
      bool recruitCreature(unit *creature);
};

#endif

/* Last Version: Jonan */
