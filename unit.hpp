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
/// The unit class.
/// @author Jonan

#ifndef UNIT_HPP
#define UNIT_HPP

#include <SDL/SDL.h>

// @{
/// Types of units
#define SKELETON 0
#define ORC      1
// @}

class cell;
class hero;

/// @todo Put more than one sprite for each unit.
/*struct sprite {
   int numberSprites;
   SDL_Surface *image[];
};*/

/// Stores the unit's atributes.
///
/// -no detailed description-
class unit {
   protected:
      int type;

      int number; // Number of units

      int live, liveMax; // Actual and maximun live
      int magic, magicMax; // Actual and maximun magic power

      int physicalDefence, physicalAttack;
      int magicalDefence, magicalAttack;
      int agility;

      int movement; // The creatures speed

      SDL_Surface *image; // The unit's image
      bool selected; // Indicates if the unit is selected

      cell *position; // The cell where the unit is
      hero *master; // The hero that controls the unit.

      // Sets all the unit's attributes.
      void setAllAttributes(const int live, const int magic, const int physicalDefence,
                            const int magicalDefence, const int physicalAttack,
                            const int magicalAttack, const int agility,
                            const int movement);
      // Sets the creatures attributes acording to his type.
      // (Implemented in unit_type.cpp)
      virtual void setCreaturesAttributes(void);

   public:
      /// @param[in] type Type of unit.
      /// @param[in] number Number of units.
      unit(const int type, const int number = 1); // Constructor
      ~unit(void) {} // Destructor

      /// Changes the number of units.
      ///
      /// -no detailed description-
      ///
      /// @param[in] number Number of units.
      void setNumber(const int number);
      /// Sets the creature's image.
      ///
      /// -no detailed description-
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      void setImage(const char *imageName);
      /// Changes the unit's position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] position The cell where the unit is.
      void setPosition(cell &position);
      /// Changes the hero that controls the unit.
      ///
      /// -no detailed description-
      ///
      /// @param[in] master Hero that controls the unit.
      void setMaster(hero *master);

      /// Returns the number of units.
      ///
      /// -no detailed description-
      ///
      /// @return Number of units.
      int getNumber(void);
      /// Returns the unit's movement.
      ///
      /// -no detailed description-
      ///
      /// @return Unit's movement.
      int getMovement(void);
      /// Returns the unit's agility.
      ///
      /// -no detailed description-
      ///
      /// @return Unit's agility.
      int getAgility(void);
      /// Returns the cell where the unit is.
      ///
      /// -no detailed description-
      ///
      /// @return The cell where the unit is.
      cell* getPosition(void);
      /// Returns the hero that controls the unit.
      ///
      /// -no detailed description-
      ///
      /// @return The hero that controls the unit.
      hero* getMaster(void);

      /// Attacks a given unit.
      ///
      /// -no detailed description-
      ///
      /// @param[in] creature Unit to attack.
      /// @return The unit attacked.
      unit* attack(unit &creature);

      /// Draws the creature in the given position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] position The position where the creature should be drawn.
      virtual void draw(SDL_Rect &position);
};

#endif // UNIT_HPP
