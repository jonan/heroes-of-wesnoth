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
#include "unit_type.hpp"

// Constructor
unit::unit(const char *type, const int number) {
   this->number = number;
   if (type != NULL) { // It should only be NULL when the unit is a hero.
      this->type = strdup(type);
      setCreaturesAttributes(this);
   }
   position = NULL;
}

// Destructor
unit::~unit(void) {
   delete [] type;
}

// Sets all the unit's attributes.
void unit::setAllAttributes(int live, int magic, int physicalDefence,
                           int magicalDefence, int physicalAttack,
                           int magicalAttack, int agility,
                           int movement) {
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

// Sets the creature's image.
void unit::setNumber(const int number) {
   this->number = number;
}

// Sets the creature's image.
void unit::setImage(const char *imageName) {
   image = screen->getImage(imageName);
}

// Changes the unit's position.
void unit::setPosition(cell *position) {
   this->position = position;
}

// Returns the unit's movement.
int unit::getMovement(void) {
   return movement;
}

// Returns the unit's type.
char* unit::getType(void) {
   return type;
}

// Selects the unit.
void unit::select(void) {
   selected = true;
}

// Unselects the unit.
void unit::unselect(void) {
   selected = false;
}

// Indicates if the unit is selected (true) or not (false).
bool unit::isSelected(void) {
   return selected;
}

// Draws the creature in the given position.
void unit::draw(SDL_Rect *position) {
   char text[3];

   screen->draw(image, position);
   sprintf(text, "%i", number);
   screen->write(text, position->x+17, position->y+52);
}
