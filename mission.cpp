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

// Creates and starts a mission.
void createMission( const char *map,
                    const int width, const int height,
                    const int positionX, const int positionY,
                    const int numberAlies
                  ) {
   unit *temp;

   hero *player;
   world war(map, width, height);

   player = new hero(FIGHTER, HUMAN);
   // Set the hero's units.
   for (int j=0; j<9; j++) {
      temp = new unit(SERGEANT, numberAlies);
      player->recruitCreature(temp);
   }

   war.setHero(*player, positionX, positionY);
   war.start();
}

// Creates and starts mission 1.
void mission1(void) {
   createMission("mission1", 30, 15, 1, 1, 10);
}

// Creates and starts mission 1.
void mission2(void) {
   createMission("mission2", 30, 26, 3, 5, 15);
}

// Creates and starts mission 1.
void mission3(void) {
   createMission("mission3", 30, 20, 8, 4, 25);
}
