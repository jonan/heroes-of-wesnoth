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
along with Heroes of Wesnoth. If not, see <http://www.gnu.org/licenses/>
*/

#include "mission.hpp"

#include "hero.hpp"
#include "world.hpp"

// Creates and starts a mission.
void createMission(const char *map, const char *hero_type,
                   const int hero_position_x, const int hero_position_y,
                   const char *allies_type, const int number_allies
                  ) {
   World war(map);
   Hero *hero = new Hero(hero_type);

   Unit *temp;
   // Set the hero's units.
   for (int j=0; j<9; j++) {
      temp = new Unit(allies_type, number_allies);
      hero->recruitCreature(temp);
   }
   war.setHero(*hero, hero_position_x, hero_position_y);

   war.start();
}

// Create and start mission 1.
void mission1(void) {
   createMission("mission1", "undead", 2, 2, "skeleton", 10);
}

// Create and start mission 2.
void mission2(void) {
   createMission("mission2", "elf", 3, 6, "fighter", 15);
}

// Create and start mission 3.
void mission3(void) {
   createMission("mission3", "human", 4, 9, "sergeant", 25);
}
