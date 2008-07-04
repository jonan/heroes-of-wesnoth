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

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "graphics.hpp"
#include "unit.hpp"

// Sets all the unit's attributes.
void unit::setAllAttributes(const int live, const int projectiles,
                            const int attack, const int defense,
                            const int agility, const int movement
                           ) {
   this->live = live;
   liveMax = live;
   this->projectiles = projectiles;
   this->attack = attack;
   this->defense = defense;
   this->agility = agility;
   this->movement = movement;
}

// Adds an image to the standing animation.
void unit::addAnimationImage(const char *imageName, const int animation) {
   animations[animation].push_back( screen->getImage(imageName) );
}

// Constructor
unit::unit(const char type, const int number) {
   this->number = number;

   facingSide = RIGHT;
   sprite = 0;
   actualAnimation = STANDING;

   if (type != -1) { // It should only be -1 when the unit is a hero.
      this->type = type;
      setCreaturesAttributes();
      master = NULL;
   }

   position = NULL;
}

// Makes the unit face the given side
void unit::setFacingSide(const int facingSide) {
   if (this->facingSide != facingSide) {
      this->facingSide = facingSide;
      /* Adds at the end of each deque all the images but
         facing the other way, then erases the original ones */
      deque<SDL_Surface*>::iterator initialEnd;
      int initialSize;

      for (int i=0; i<NUM_ANIMATIONS; i++) {
         initialEnd = animations[i].end();
         initialSize = animations[i].size();
         // Add new images
         for (int j=0; j<initialSize; j++)
            animations[i].push_back( screen->face(facingSide, animations[i][j]) );
         // Erase previous images
         animations[i].erase(animations[i].begin(), initialEnd);
      }
   }
}

// Attacks a given unit.
void unit::attackCreature(unit &creature) {
   // Set the attacking animation
   startAnimation(ATTACKING);
   creature.startAnimation(DEFENDING);
   // Calculate the damage
   double damage;

   damage = (attack*(log(number)+1))/(creature.defense*(log(creature.number)+1));
   creature.live -= damage;
   while (creature.live <= 0 && creature.number != 0) {
      creature.live = creature.liveMax+creature.live;
      creature.number--;
   }
}

// Draws the creature in the given position.
void unit::draw(SDL_Rect &position) {
   // Get closer to the enemy when attacking
   if (actualAnimation == ATTACKING) {
      if (facingSide == RIGHT) position.x += 10;
      else position.x -= 10;
   }
   if (animations[actualAnimation].size() > 0) {
      // Draw the corresponding sprite.
      screen->draw(animations[actualAnimation][sprite/NUM_FRAMES_FOR_SPRITE], position);
      sprite++;
      // Check if this was the last sprite and go back to standing if it was.
      if ( (sprite/NUM_FRAMES_FOR_SPRITE) == (int) animations[actualAnimation].size() ) {
         sprite = 0;
         actualAnimation = STANDING;
      }
   } else { // The animation is ATTACKING
      // If there's no animation for attack simply get the creature closer to the enemy
      screen->draw(animations[STANDING][0], position);
      sprite++;
      if (sprite == NUM_FRAMES_FOR_SPRITE) {
         sprite = 0;
         actualAnimation = STANDING;
      }
   }

   if (number>0) {
      char text[3];
      sprintf(text, "%i", number);
      screen->write(text, position.x+17, position.y+52);
   }
}

// Starts a given animation.
void unit::startAnimation(const int animation) {
   actualAnimation = animation;
   /* If this unit has no sprite for the given animation
      go back to STANDIGN (ATTACKING has a default animation). */
   if (animations[actualAnimation].size() > 0 || actualAnimation == ATTACKING)
      sprite = 0;
   else
      actualAnimation = STANDING;
}
