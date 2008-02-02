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

#include "hero.hpp"

// Constructor
hero::hero(const char *type) {
   // The hero starts controling no creatures
   for (int i=0; i<MAX_UNITS; i++) {
      creature[i]=NULL;
   }
   numCreatures=0;
}

// If the hero can't control a new creature (he already
// controls 9) returns false, else returns true.
bool hero::recruitCreature(unit *creature) {
   if (numCreatures == MAX_UNITS) return false;
   else {
      this->creature[numCreatures]=creature;
      numCreatures+=1;
      return true;
   }
}
