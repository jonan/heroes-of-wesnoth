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

#include "mission.hpp"

#include "hero.hpp"
#include "world.hpp"

// Constructor
Mission::Mission(const char *map, const int number_allies,
                 const int width, const int height,
                 const int hero_position_x, const int hero_position_y
                ) {
  war = new World(map, width, height);
  player = new Hero(HUMAN);
  this->number_allies = number_allies;
  this->hero_position_x = hero_position_x;
  this->hero_position_y = hero_position_y;
}

// Destructor
Mission::~Mission() {
  delete war;
}

// Launches the mission
void Mission::startMission() {
  Unit *temp;

  for ( int i=0; i < 9; i++ ) {
    temp = new Unit(SERGEANT, number_allies);
    player->recruitCreature(temp);
  }

  war->setHero(*player, hero_position_x, hero_position_y);
  war->start();
}

// Creates and starts mission 1.
void mission1(void) {
  Mission mission_1("mission1", 10, 32, 17, 2, 2);
  mission_1.startMission();
}

// Creates and starts mission 2.
void mission2(void) {
  Mission mission_2("mission2", 15, 32, 28, 3, 6);
  mission_2.startMission();
}

// Creates and starts mission 3.
void mission3(void) {
  Mission mission_3("mission3", 25, 32, 22, 4, 9);
  mission_3.startMission();
}
