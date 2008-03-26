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

#include "graphics.hpp"
#include "unit.hpp"

// Sets all the unit's attributes.
void unit::setAllAttributes(const int live, const int magic, const int physicalDefence,
                            const int magicalDefence, const int physicalAttack,
                            const int magicalAttack, const int agility,
                            const int movement) {
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

// Constructor
unit::unit(const int type, const int number) {
   this->number = number;
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

// Sets the creature's image.
void unit::setImage(const char *imageName) {
   image = screen->getImage(imageName);
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

// Returns the hero that controls the unit.
hero* unit::getMaster(void) {
   return master;
}

// Attacks a given unit.
unit* unit::attack(unit &creature) {
   /// @todo improve attacks
   if (creature.number > 0) creature.number--;
   if (creature.number == 0) return NULL;
   else return &creature;
}

// Draws the creature in the given position.
void unit::draw(SDL_Rect &position) {
   char text[3];

   screen->draw(image, position);
   sprintf(text, "%i", number);
   screen->write(text, position.x+17, position.y+52);
}
