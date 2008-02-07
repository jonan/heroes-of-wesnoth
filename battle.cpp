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

#include "battle.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "timer.hpp"

// Processes the new input and draws
// everything in the screen.
int battle::frame(void) {
   if (keys[SDLK_ESCAPE]) return 1;
   battleMap->moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   battleMap->draw();
   return 0;
}

// Constructor
battle::battle(void) {
   battleMap = new map(18, 9);
   player = new hero("fighter");
   player->setAllAttributes(1, 1, 1, 1, 1, 1, 2, 3);
   player->setImage("grand-knight");
   battleMap->setTerrain("grassland-r1");
   battleMap->setHero(player);
}

// Starts the battle.
void battle::start(void) {
   screen->erase();

   /// @todo use the loop function in loop.hpp
   int done=0;
   timer fps;

   while (done == 0) {
      fps.start();
      input->readInput();
      if (input->getType() == SYSTEM)
         if (input->getSystemType() == QUIT)
            done = 1;
      done = frame();
      screen->update();
      fps.end(50);
   }
}

// Creates and starts a battle.
void createBattle(void) {
   battle war;
   war.start();
}
