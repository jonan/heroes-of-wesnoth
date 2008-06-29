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

#define MAX_UNITS 9

// @{
/// Types of heros
#define FIGHTER 0
#define WIZARD  1
// @}

// @{
/// Types of AI
#define HUMAN    0
#define COMPUTER 1
// @}

/// Stores the hero's atributes.
///
/// -no detailed description-
class hero : public unit {
   private:
      int ai; // Type of Artificial Intelligence
      int visibility; // How far the hero sees

      unit *creature[MAX_UNITS]; // The creatures a hero can control

      // Sets the heros attributes acording to his type.
      // (Implemented in hero_type.cpp)
      void setCreaturesAttributes(void);

   public:
      /// @param[in] type Type of hero.
      /// @param[in] ai Type of AI.
      hero(const int type, const int ai); // Constructor
      ~hero(void); // Destructor

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
      unit* getCreature(const int number) {return creature[number];}

      /// Assings a new creature to the hero.
      ///
      /// If the hero can't control a new creature (he already
      /// controls 9) returns false, else returns true.
      ///
      /// @param[in] creature The new unit the hero can control.
      /// @return If the recruitment was successful or not.
      bool recruitCreature(unit *creature);
      /// Assings a new creature to the hero.
      ///
      /// -no detailed description-
      ///
      /// @param[in] creature The new unit the hero can control.
      /// @param[in] position Position were the unit should be.
      /// @return The unit that was in that position.
      unit* recruitCreature(unit *creature, const unsigned int position);

      /// Draws the hero in the given position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] position The position where the hero should be drawn.
      void draw(SDL_Rect &position);
};

#endif // HERO_HPP
