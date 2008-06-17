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
/// The unit class.
/// @author Jonan

#ifndef UNIT_HPP
#define UNIT_HPP

#include <deque>

#include <SDL/SDL.h>

using namespace std;

// @{
/// Types of units.
#define ARMAGEDDON  '0'
#define BAT         '1'
#define BLADEMASTER '2'
#define CAVESPIDER  '3'
#define FLANKER     '4'
#define PILLAGER    '5'
#define SERGEANT    '6'
#define SKELETON    '7'
#define WOLF_RIDER  '8'
// @}

// @{
/// Types of animations.
#define DYING  0
// @}

/// Number of frames to wait before changing to the next sprite.
#define NUM_FRAMES_FOR_SPRITE 3

class cell;
class hero;

/// Stores the unit's atributes.
///
/// -no detailed description-
class unit {
   protected:
      char type;

      int number; // Number of units

      double live; // Actual live
      int liveMax; // Maximun live
      int magic, magicMax; // Actual and maximun magic power

      int physicalDefence, physicalAttack;
      int magicalDefence, magicalAttack;
      int agility;

      int movement; // The creatures speed

      deque<SDL_Surface*> standing;
      deque<SDL_Surface*> dying;
      int sprite; // Last sprite drawn
      int nonStandingSprite; // Last sprite of a non-standing animation drawn

      bool selected; // Indicates if the unit is selected

      cell *position; // The cell where the unit is
      hero *master; // The hero that controls the unit.

      // Sets all the unit's attributes.
      void setAllAttributes(const int live, const int magic,
                            const int physicalDefence, const int magicalDefence,
                            const int physicalAttack, const int magicalAttack,
                            const int agility, const int movement);
      // Adds an image to the standing animation.
      void addStandingImage(const char *imageName);
      // Adds an image to the dying animation.
      void addDyingImage(const char *imageName);
      // Sets the creatures attributes acording to his type.
      // (Implemented in unit_type.cpp)
      virtual void setCreaturesAttributes(void);

   public:
      /// @param[in] type Type of unit.
      /// @param[in] number Number of units.
      unit(const char type, const int number = 1); // Constructor
      ~unit(void) {} // Destructor

      /// Changes the number of units.
      ///
      /// -no detailed description-
      ///
      /// @param[in] number Number of units.
      void setNumber(const int number);
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
      /// Returns the unit's type.
      ///
      /// -no detailed description-
      ///
      /// @return The unit's Type.
      char getType(void);
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
      void attack(unit &creature);

      /// Makes the unit face left
      ///
      /// -no detailed description-
      void faceLeft(void);
      /// Makes the unit face right
      ///
      /// -no detailed description-
      void faceRight(void);

      /// Draws the creature in the given position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] position The position where the creature should be drawn.
      virtual void draw(SDL_Rect &position);
      /// Draws an animation.
      ///
      ///  -no detailed description-
      ///
      /// @param[in] position The position where the creature should be drawn.
      /// @param[in] type The type of animation.
      /// @return true when the animation finishes.
      bool animation(SDL_Rect &position, const int type);
};

#endif // UNIT_HPP
