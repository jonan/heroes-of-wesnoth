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

#include "hero.hpp"
#include "mission.hpp"
#include "world.hpp"

// Creates and starts mission 1.
void mission1(void) {
   unit *temp;

   hero *player;
   world war("mission1", 30, 15);

   player = new hero(FIGHTER, HUMAN);
   // Set the hero's units.
   for (int j=0; j<9; j++) {
      temp = new unit(SERGEANT, 10);
      player->recruitCreature(temp);
   }

   war.setEnemies("mission1_creatures");
   war.setHero(*player, 1, 1);
   war.start();
}

// Creates and starts mission 1.
void mission2(void) {
   unit *temp;

   hero *player;
   world war("mission2", 30, 26);

   player = new hero(FIGHTER, HUMAN);
   // Set the hero's units.
   for (int j=0; j<9; j++) {
      temp = new unit(SERGEANT, 15);
      player->recruitCreature(temp);
   }

   war.setEnemies("mission2_creatures");
   war.setHero(*player, 3, 5);
   war.start();
}

// Creates and starts mission 1.
void mission3(void) {
   unit *temp;

   hero *player;
   world war("mission3", 30, 20);

   player = new hero(FIGHTER, HUMAN);
   // Set the hero's units.
   for (int j=0; j<9; j++) {
      temp = new unit(SERGEANT, 25);
      player->recruitCreature(temp);
   }

   war.setEnemies("mission3_creatures");
   war.setHero(*player, 8, 4);
   war.start();
}
