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
#define ARCHER      '0'
#define ARMAGEDDON  '1'
#define BAT         '2'
#define BLADEMASTER '3'
#define CAVESPIDER  '4'
#define FLANKER     '5'
#define PILLAGER    '6'
#define SERGEANT    '7'
#define SKELETON    '8'
#define WOLF_RIDER  '9'
// @}

// @{
/// Types of animations.
#define ATTACKING      0
#define DEFENDING      1
#define DYING          2
#define STANDING       3
#define NUM_ANIMATIONS 4
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
      int facingSide; // Indicates if the creature is facing left or right

      double live; // Actual live
      int liveMax; // Maximun live
      int projectiles; // Number of projectiles a unit can shoot.
      int attack, defense, agility, movement; // Unit's atributes

      deque<SDL_Surface*> animations[NUM_ANIMATIONS];
      int actualAnimation;

      int sprite; // Last sprite drawn
      int nonStandingSprite; // Last sprite of a non-standing animation drawn

      cell *position; // The cell where the unit is
      hero *master; // The hero that controls the unit.

      // Sets all the unit's attributes.
      void setAllAttributes(const int live, const int projectiles,
                            const int attack, const int defense,
                            const int agility, const int movement);
      // Adds an image to the an animation.
      void addAnimationImage(const char *imageName, const int animation);
      // Sets the creatures attributes acording to his type.
      // (Implemented in unit_type.cpp)
      virtual void setCreaturesAttributes(void);

   public:
      /// @param[in] type Type of unit.
      /// @param[in] number Number of units.
      unit(const char type, const int number = 1); // Constructor
      virtual ~unit(void) {} // Destructor

      /// Changes the number of units.
      ///
      /// -no detailed description-
      ///
      /// @param[in] number Number of units.
      void setNumber(const int number) {this->number = number;}
      /// Changes the unit's position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] position The cell where the unit is.
      void setPosition(cell &position) {this->position = &position;}
      /// Changes the hero that controls the unit.
      ///
      /// -no detailed description-
      ///
      /// @param[in] master Hero that controls the unit.
      void setMaster(hero *master) {this->master = master;}
      /// Makes the unit face the given side
      ///
      /// -no detailed description-
      ///
      /// @param[in] facingSide Side to face.
      void setFacingSide(const int facingSide);

      /// Returns the number of units.
      ///
      /// -no detailed description-
      ///
      /// @return Number of units.
      int getNumber(void) {return number;}
      /// Returns the unit's movement.
      ///
      /// -no detailed description-
      ///
      /// @return Unit's movement.
      int getMovement(void) {return movement;}
      /// Returns the unit's agility.
      ///
      /// -no detailed description-
      ///
      /// @return Unit's agility.
      int getAgility(void) {return agility;}
      /// Returns the cell where the unit is.
      ///
      /// -no detailed description-
      ///
      /// @return The cell where the unit is.
      cell* getPosition(void) {return position;}
      /// Returns the unit's type.
      ///
      /// -no detailed description-
      ///
      /// @return The unit's Type.
      char getType(void) {return type;}
      /// Returns the hero that controls the unit.
      ///
      /// -no detailed description-
      ///
      /// @return The hero that controls the unit.
      hero* getMaster(void) {return master;}

      /// Attacks a given unit.
      ///
      /// -no detailed description-
      ///
      /// @param[in] creature Unit to attack.
      void attackCreature(unit &creature);

      /// Draws the creature in the given position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] position The position where the creature should be drawn.
      /// @param[in] animation Type of animation to draw (default continues current animation).
      virtual void draw(SDL_Rect &position, const int animation = -1);
};

#endif // UNIT_HPP
