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
/// The Unit class.
/// @author Jonan

#ifndef UNIT_HPP
#define UNIT_HPP

#include <deque>
#include <string>

#include "graphics.hpp"
#include "util.hpp"

struct SDL_Rect;
struct SDL_Surface;

class Cell;
class Hero;

struct SpecialImage;

/// Types of projectiles.
enum {WHITE_MISSILE};

/// Types of animations.
enum {ATTACKING,
      DEFENDING,
      DYING,
      IDLE,
      STANDING,
      NUM_ANIMATIONS};

/// Stores a unit's attributes.
class Unit {
  public:
    /// @param[in] type Type of unit (name or id).
    /// @param[in] number Number of units.
    Unit(const char *type, const int number); // Constructor
    virtual ~Unit(void); // Destructor

    // @{
    /// Set functions.
    void setPosition   (Cell &position)         {this->position = &position;}
    void setMaster     (Hero *master)           {this->master = master;     }
    void setAnimation  (const int animation);
    void setFacingSide (const int facing_side);
    // @}

    // @{
    /// Get functions.
    int         getNumber          (void)                 {return number;          }
    int         getMovement        (void)                 {return movement;        }
    int         getAgility         (void)                 {return agility;         }
    int         getProjectiles     (void)                 {return projectiles;     }
    int         getProjectilesType (void)                 {return projectiles_type;}
    Cell*       getPosition        (void)                 {return position;        }
    const char* getId              (void)                 {return type.c_str();    }
    Hero*       getMaster          (void)                 {return master;          }
    int         getNumFrames       (const int animation);
    // @}

    /// Makes this creature inflict damage to another creature.
    /// @param[in] creature Creature to damage.
    void damageCreature(Unit &creature);

    // Adds a magic animation.
    void addMagicAnimation(const int spell);

    /// Draws the creature in the given position.
    /// @param[in] position The position where the creature should be drawn.
    virtual void draw(SDL_Rect &position);

  protected:
    // Sets the creature's attributes acording to his type.
    void setCreaturesAttributes(const char *xml_file);

    // Draws the creature in the given position.
    void drawUnit(SDL_Rect &position);

    std::string type;

    Hero *master;   // The hero that controls the unit.

  private:
    // Sets all the unit's attributes.
    void setAllAttributes(const int live, const int movement,
                          const int attack, const int agility,
                          const int projectiles, const int projectiles_type);

    // Adds an image to a given animation.
    void addAnimationImage(const char *image_name, const int animation);

    int number;      // Number of units
    int facing_side; // Indicates if the creature is facing left or right

    double live;                   // Actual live
    int live_max;                  // Maximun live
    int attack, agility, movement; // Unit's attributes
    int projectiles;               // Number of projectiles a unit can shoot.
    int projectiles_type;

    int num_frames_per_sprite;
    std::deque<SDL_Surface*> animations[NUM_ANIMATIONS];
    int actual_animation;
    SpecialImage *magic_spell;

    int sprite; // Last sprite drawn

    Cell *position; // The cell where the unit is

    DISALLOW_COPY_AND_ASSIGN(Unit);
};

#endif // UNIT_HPP
