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

// Constructor
unit::unit(void) {
   imageName = NULL;
}

// Destructor
unit::~unit(void) {
   delete imageName;
}

// Sets all the unit's attributes.
void unit::setAllAttributes(int live, int magic, int physicalDefence,
                           int magicalDefence, int physicalAttack,
                           int magicalAttack, int movement) {
   this->live = live;
   liveMax = live;
   this->magic = magic;
   magicMax = magic;
   this->physicalDefence = physicalDefence;
   this->physicalAttack = physicalAttack;
   this->magicalDefence = magicalDefence;
   this->magicalAttack = magicalAttack;
   this->movement = movement;
}

// Sets the creature's image.
void unit::setImage(const char *imageName) {
   this->imageName = strdup(imageName);
}

// Returns the unit's movement.
int unit::getMovement(void) {
   return movement;
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
   screen->draw(imageName, position);
}

/* Last Version: Jonan */
