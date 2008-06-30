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

// Creates and starts mission 1.
void mission1(void) {
   Mission *mission_1 = new Mission("mission1", 30, 15, 1, 1, 10);
   mission_1->startMission();
}

// Creates and starts mission 2.
void mission2(void) {
   Mission *mission_2 = new Mission("mission2", 30, 26, 3, 5, 15);
   mission_2->startMission();
}

// Creates and starts mission 3.
void mission3(void) {
   Mission *mission_3 = new Mission("mission3", 30, 20, 4, 8, 25);
   mission_3->startMission();
}

Mission::Mission(  const char *map, const int width,
                   const int height, const int heroPositionX,
                   const int heroPositionY, const int numberAllies ) {
   war = new world( map, width, height );
   player = new hero( FIGHTER, HUMAN );
   this->heroPositionX = heroPositionX;
   this->heroPositionY = heroPositionY;
   this->numberAllies = numberAllies;
}

Mission::~Mission() {
   delete war;
   delete player;
}

void Mission::startMission() {
   unit *temp;

   for ( int i=0; i < 9; i++ ) {
      temp = new unit( SERGEANT, numberAllies );
      player->recruitCreature( temp );
   }

   war->setHero( *player, heroPositionX, heroPositionY );
   war->start();
}
