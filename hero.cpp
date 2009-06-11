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
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include "hero.hpp"

// Constructor
Hero::Hero(const int type) : Unit(-1, 1) {
  master = this;
  this->type = type;
  setCreaturesAttributes();
  // The hero starts controling no creatures
  for (int i=0; i<MAX_UNITS; i++) {
    creature[i]=NULL;
  }

  visibility = 8;
}

Hero::~Hero(void) {
  for (int i=0; i<MAX_UNITS; i++) {
    if (creature[i]) delete creature[i];
  }
}

// Assings a new creature to the hero.
void Hero::recruitCreature(Unit *creature, const int position) {
  if (position != -1) {
    this->creature[position] = creature;
    if (creature) this->creature[position]->setMaster(this);
  } else {
    bool found = false;
    for (int i = 0; i<MAX_UNITS && !found; i++) {
      if (this->creature[i] == NULL) {
        this->creature[i] = creature;
        if (creature) this->creature[i]->setMaster(this);
        found = true;
      }
    }
  }
}
