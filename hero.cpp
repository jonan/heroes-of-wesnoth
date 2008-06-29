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

#include "graphics.hpp"
#include "hero.hpp"

// Constructor
hero::hero(const int type, const int ai) : unit(-1) {
   master = this;
   this->type = type;
   this->ai = ai;
   setCreaturesAttributes();
   // The hero starts controling no creatures
   for (int i=0; i<MAX_UNITS; i++) {
      creature[i]=NULL;
   }

   visibility = 8;
}

hero::~hero(void) {
   for (int i=0; i<MAX_UNITS; i++) {
      if (creature[i]) delete creature[i];
   }
}

// If the hero can't control a new creature (he already
// controls 9) returns false, else returns true.
bool hero::recruitCreature(unit *creature) {
   bool done = false;
   int i = 0;

   while (i<MAX_UNITS && !done) {
      if (this->creature[i] == NULL) {
         this->creature[i] = creature;
         this->creature[i]->setMaster(this);
         done = true;
      } else i++;
   }

   return done? true:false;
}

// Assings a new creature to the hero.
unit* hero::recruitCreature(unit *creature, const unsigned int position) {
   unit *temp;

   if (position < MAX_UNITS) {
      temp = this->creature[position];
      this->creature[position] = creature;
      return temp;
   } else return NULL;
}

// Draws the hero in the given position.
void hero::draw(SDL_Rect &position) {
   // Draw the corresponding sprite.
   screen->draw(standing[sprite/NUM_FRAMES_FOR_SPRITE], position);
   // Increase the sprite.
   sprite++;
   // Check if this was the last sprite and start again if it was.
   if ( (sprite/NUM_FRAMES_FOR_SPRITE) == (int) standing.size() )
      sprite = 0;
}
