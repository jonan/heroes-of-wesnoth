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

#include <cmath>

#include "graphics.hpp"
#include "unit.hpp"

// Sets all the unit's attributes.
void unit::setAllAttributes(const int live, const int magic,
                            const int physicalDefence, const int magicalDefence,
                            const int physicalAttack, const int magicalAttack,
                            const int agility, const int movement
                           ) {
   this->live = live;
   liveMax = live;
   this->magic = magic;
   magicMax = magic;
   this->physicalDefence = physicalDefence;
   this->physicalAttack = physicalAttack;
   this->magicalDefence = magicalDefence;
   this->magicalAttack = magicalAttack;
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
   }

   position = NULL;
   master = NULL;
}

// Changes the number of units.
void unit::setNumber(const int number) {
   this->number = number;
}

// Changes the unit's position.
void unit::setPosition(cell &position) {
   this->position = &position;
}

// Changes the hero that controls the unit.
void unit::setMaster(hero *master) {
   this->master = master;
}

// Returns the number of units.
int unit::getNumber(void) {
   return number;
}

// Returns the unit's movement.
int unit::getMovement(void) {
   return movement;
}

// Returns the unit's agility.
int unit::getAgility(void) {
   return agility;
}

// Returns the cell where the unit is.
cell* unit::getPosition(void) {
   return position;
}

// Returns the unit's type.
char unit::getType(void) {
   return type;
}

// Returns the hero that controls the unit.
hero* unit::getMaster(void) {
   return master;
}

// Attacks a given unit.
void unit::attack(unit &creature) {
   creature.live -= physicalAttack * ( log(number)+1 );
   while (creature.live <= 0 && creature.number != 0) {
      creature.live = creature.liveMax+creature.live;
      creature.number--;
   }
}

// Draws the creature in the given position.
void unit::draw(SDL_Rect &position) {
   // Draw the corresponding sprite.
   screen->draw(standing[sprite/NUM_FRAMES_FOR_SPRITE], position);
   // Increase the sprite.
   sprite++;
   // Check if this was the last sprite and start again if it was.
   if ( (sprite/NUM_FRAMES_FOR_SPRITE) == standing.size() )
      sprite = 0;

   if (number>0) {
      char text[3];
      sprintf(text, "%i", number);
      screen->write(text, position.x+17, position.y+52);
   }
}

// Draws an animation.
bool unit::animation(SDL_Rect &position, const int type) {
   if (type == DYING) {
      // Draw the corresponding sprite.
      screen->draw(dying[nonStandingSprite/NUM_FRAMES_FOR_SPRITE], position);
      // Increase the sprite.
      nonStandingSprite++;
      // Check if this was the last sprite and start again if it was.
      if ( (nonStandingSprite/NUM_FRAMES_FOR_SPRITE) == dying.size() ) {
         nonStandingSprite = 0;
         return false;
      } else return true;
   }
}
