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

#include "unit.hpp"

/*
unit::unit(char tipe[20]) {

}

unit::~unit() {
   delete image;
}
*/

// Sets all the unit's atributes
void unit::setAllAtributes(int live, int magic, int fis_def, int fis_attack, int mag_def, int mag_attack, int movement) {
   this->live = live;
   live_max = live;
   this->magic = magic;
   magic_max = magic;
   this->fis_def = fis_def;
   this->fis_attack = fis_attack;
   this->mag_def = mag_def;
   this->mag_attack = mag_attack;
   this->movement = movement;
}
/* ----------------------------------------------------------------------------------------------------------------------- */
void unit::setImage(const char *imageName) {
   image = new char [strlen(imageName)];

   strcpy(image, imageName);
}

void unit::draw(graphics *screen, SDL_Rect *position) {
   screen->draw(image, position);
}

bool unit::isSelected() {
   return selected;
}

void unit::select() {
   selected=true;
}

void unit::unselect() {
   selected=false;
}

int unit::getMovement() {
   return movement;
}

/* Last Version: Jonan */
