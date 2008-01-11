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

#ifndef UNIT_HPP
#define UNIT_HPP

#include <SDL/SDL.h>

/// Stores the unit's atributes.
///
/// -no detailed description-
class unit {
   protected:
      int live, liveMax; // Actual and maximun live
      int magic, magicMax; // Actual and maximun magic power

      int physicalDefence, physicalAttack;
      int magicalDefence, magicalAttack;

      int movement; // The creatures speed

      char *imageName; // The name of the unit's image
      bool selected; // Indicates if the unit is selected

   public:
      unit(void); // Constructor
      ~unit(void); // Destructor

      /// Sets all the unit's attributes.
      ///
      /// -no detailed description-
      ///
      /// @param [in] live Maximum live.
      /// @param [in] magic Maximum magic power.
      /// @param [in] physicalDefence Defence against physical attacks.
      /// @param [in] magicalDefence Defence against magical attacks.
      /// @param [in] physicalAttack Power of the physical attack.
      /// @param [in] magicalAttack Power of the magical attack.
      /// @param [in] movement Speed of the creature.
      void setAllAttributes(int live, int magic, int physicalDefence,
                           int magicalDefence, int physicalAttack,
                           int magicalAttack, int movement);
      /// Sets the creature's image.
      ///
      /// -no detailed description-
      ///
      /// @param [in] imageName The image's name, without the "img/" or the ".png".
      void setImage(const char *imageName);
      /// Returns the unit's movement.
      ///
      /// -no detailed description-
      ///
      /// @return Unit's movement.
      int getMovement(void);
      /// Selects the unit.
      ///
      /// -no detailed description-
      void select(void);
      /// Unselects the unit.
      ///
      /// -no detailed description-
      void unselect(void);
      /// Indicates if the unit is selected (true) or not (false).
      ///
      /// -no detailed description-
      ///
      /// @return If unit is selected, true, else, false.
      bool isSelected(void);
      /// Draws the creature in the given position.
      ///
      /// -no detailed description-
      ///
      /// @param [in] position The position where the creature should be drawn.
      void draw(SDL_Rect *position);
};

#endif

/* Last Version: Jonan */
