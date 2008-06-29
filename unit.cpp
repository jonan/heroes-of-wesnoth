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
void unit::addStandingImage(const char *imageName) {
   standing.push_back( screen->getImage(imageName) );
}

// Adds an image to the dying animation.
void unit::addDyingImage(const char *imageName) {
   dying.push_back( screen->getImage(imageName) );
}

// Constructor
unit::unit(const char type, const int number) {
   this->number = number;

   sprite = 0;
   nonStandingSprite = 0;

   if (type != -1) { // It should only be -1 when the unit is a hero.
      this->type = type;
      setCreaturesAttributes();
      master = NULL;
   }

   position = NULL;
}

// Attacks a given unit.
void unit::attackCreature(unit &creature) {
   double damage;

   damage = (attack*(log(number)+1))/(creature.defense*(log(creature.number)+1));
   creature.live -= damage;
   while (creature.live <= 0 && creature.number != 0) {
      creature.live = creature.liveMax+creature.live;
      creature.number--;
   }
}

// Makes the unit face left
void unit::faceLeft(void) {
   /// @todo Check this
   /* Adds at the end of each deque all the images
      but facing left, then erases the original ones */
   deque<SDL_Surface*>::iterator initialEnd;
   int initialSize;

   // Change standing images
   initialEnd = standing.end();
   initialSize = standing.size();
   // Add new images
   for (int i=0; i<initialSize; i++)
      standing.push_back( screen->faceLeft(standing[i]) );
   // Erase previous images
   standing.erase(standing.begin(), initialEnd);

   // Change dying images
   initialEnd = dying.end();
   initialSize = dying.size();
   // Add new images
   for (int i=0; i<initialSize; i++)
      dying.push_back( screen->faceLeft(dying[i]) );
   // Erase previous images
   dying.erase(dying.begin(), initialEnd);
}

// Makes the unit face right
void unit::faceRight(void) {
   /// @todo Check this
   /* Adds at the end of each deque all the images
      but facing right, then erases the original ones */
   deque<SDL_Surface*>::iterator initialEnd;
   int initialSize;

   // Change standing images
   initialEnd = standing.end();
   initialSize = standing.size();
   // Add new images
   for (int i=0; i<initialSize; i++)
      standing.push_back( screen->faceRight(standing[i]) );
   // Erase previous images
   standing.erase(standing.begin(), initialEnd);

   // Change dying images
   initialEnd = dying.end();
   initialSize = dying.size();
   // Add new images
   for (int i=0; i<initialSize; i++)
      dying.push_back( screen->faceRight(dying[i]) );
   // Erase previous images
   dying.erase(dying.begin(), initialEnd);
}

// Draws the creature in the given position.
void unit::draw(SDL_Rect &position) {
   // Draw the corresponding sprite.
   screen->draw(standing[sprite/NUM_FRAMES_FOR_SPRITE], position);
   // Increase the sprite.
   sprite++;
   // Check if this was the last sprite and start again if it was.
   if ( (sprite/NUM_FRAMES_FOR_SPRITE) == (int) standing.size() )
      sprite = 0;

   if (number>0) {
      char text[3];
      sprintf(text, "%i", number);
      screen->write(text, position.x+17, position.y+52);
   }
}
