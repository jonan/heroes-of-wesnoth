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
/// The Unit class.
/// @author Jonan

#ifndef UNIT_HPP
#define UNIT_HPP

#include <deque>

#include <SDL/SDL.h>

#include "macros.hpp"
#include "structs.hpp"

class Cell;
class Hero;

/// Sides to face
enum {RIGHT, LEFT};

/// Types of units.
enum {ARCHER = '0',
      ARMAGEDDON,
      BAT,
      BLADE_MASTER,
      BLOOD_BAT,
      CAVE_SPIDER,
      CHAMPION,
      DEATH_BLADE,
      FIGHTER,
      FLANKER,
      PILLAGER = 'a',
      RANGER,
      SERGEANT,
      SHYDE,
      SKELETON,
      WOLF_RIDER,
      LAST_UNIT = WOLF_RIDER};

/// Types of projectiles.
enum {WHITE_MISSILE};

/// Types of animations.
enum {ATTACKING,
      DEFENDING,
      DYING,
      IDLE,
      STANDING,
      NUM_ANIMATIONS};

/// Number of frames to wait before changing to the next sprite.
const int NUM_FRAMES_FOR_SPRITE = 3;

/// Stores the unit's attributes.
///
/// -no detailed description-
class Unit {
  public:
    /// @param[in] type Type of unit.
    /// @param[in] number Number of units.
    Unit(const char type, const int number); // Constructor
    virtual ~Unit(void) {} // Destructor

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
    void setPosition(Cell &position) {this->position = &position;}
    /// Changes the hero that controls the unit.
    ///
    /// -no detailed description-
    ///
    /// @param[in] master Hero that controls the unit.
    void setMaster(Hero *master) {this->master = master;}
    /// Makes the unit face the given side
    ///
    /// -no detailed description-
    ///
    /// @param[in] facing_side Side to face.
    void setFacingSide(const int facing_side);

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
    /// Returns the unit's projectiles.
    ///
    /// -no detailed description-
    ///
    /// @return Unit's agility.
    int getProjectiles(void) {return projectiles;}
    /// Returns the cell where the unit is.
    ///
    /// -no detailed description-
    ///
    /// @return The cell where the unit is.
    Cell* getPosition(void) {return position;}
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
    Hero* getMaster(void) {return master;}
    /// Returns the number of sprites of an animation.
    ///
    /// -no detailed description-
    ///
    /// @return Number of sprites of the animation.
    int getNumSprites(const int animation) {return animations[animation].size();}

    /// Attacks a given unit.
    ///
    /// -no detailed description-
    ///
    /// @param[in] creature Unit to attack.
    void attackCreature(Unit &creature);

    /// Draws the creature in the given position.
    ///
    /// -no detailed description-
    ///
    /// @param[in] position The position where the creature should be drawn.
    virtual void draw(SDL_Rect &position);
    /// Starts a given animation.
    ///
    /// -no detailed description-
    ///
    /// @param[in] animation Type of animation.
    void startAnimation(const int animation);

  protected:
    // Sets all the unit's attributes.
    void setAllAttributes(const int live, const int movement,
                          const int attack, const int agility,
                          const int projectiles, const int projectiles_type);
    // Adds an image to the an animation.
    void addAnimationImage(const char *image_name, const int animation);
    // Adds a magic animation.
    // (Implemented in unit_magic.cpp)
    void addMagicAnimation(const int spell);

    // Sets the creature's attributes acording to his type.
    // (Implemented in unit_type.cpp)
    virtual void setCreaturesAttributes(void);

    char type;

    int number; // Number of units
    int facing_side; // Indicates if the creature is facing left or right

    double live; // Actual live
    int live_max; // Maximun live
    int projectiles; // Number of projectiles a unit can shoot.
    int projectiles_type;
    int attack, agility, movement; // Unit's attributes

    std::deque<SDL_Surface*> animations[NUM_ANIMATIONS];
    int actual_animation;
    SpecialImage *magic_spell;

    int sprite; // Last sprite drawn

    Cell *position; // The cell where the unit is
    Hero *master; // The hero that controls the unit.

  private:
    DISALLOW_COPY_AND_ASSIGN(Unit);
};

#endif // UNIT_HPP
