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
#include "hero.hpp"

// Constructor
hero::hero(const int type) : unit(-1) {
   this->type = type;
   setCreaturesAttributes();
   // The hero starts controling no creatures
   for (int i=0; i<MAX_UNITS; i++) {
      creature[i]=NULL;
   }
   numCreatures=0;
}

// Returns the number of creatures the hero controls.
int hero::getNumberCreatures(void) {
   return numCreatures;
}

// Returns a creature controled by the hero.
unit* hero::getCreature(int number) {
   if (number < numCreatures) return creature[number];
   else return NULL;
}

// If the hero can't control a new creature (he already
// controls 9) returns false, else returns true.
bool hero::recruitCreature(unit *creature) {
   if (numCreatures == MAX_UNITS) return false;
   else {
      this->creature[numCreatures]=creature;
      this->creature[numCreatures]->setMaster(this);
      numCreatures+=1;
      return true;
   }
}

// Draws the hero in the given position.
void hero::draw(SDL_Rect *position) {
   screen->draw(image, position);
}
