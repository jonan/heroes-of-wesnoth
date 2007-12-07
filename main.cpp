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

/*!*************************************************************************************
 * @file This is just a experimental file used to make sure things work as they should *
 *!*************************************************************************************/

#include "events.hpp"
#include "hero.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "timer.hpp"

SDL_Rect background_pos;
SDL_Rect logo_pos;
SDL_Surface *wesnoth;
SDL_Surface *logo;

hero player("magician");
menu *mainMenu;
map battle;
graphics *screen;
timer refresh;
events input;
bool* key;
int* mouse;

void loop(void (*function)()) {
   int done=0;

   while (done == 0) {
      refresh.start();
      input.readInput();
      mouse = input.getMouse();
      key = input.getKeyboard();
      if (key[SDLK_ESCAPE]) {done = 1;}
      if (input.getType() == SYSTEM)
         if (input.getSystemType() == QUIT)
            done = 1;
      function();
      refresh.end(50);
   }
}

void drawMenu(){
   mainMenu->moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   mainMenu->draw(screen);
   screen->update();
}

void drawMap(){
   battle.moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   battle.draw(screen);
   screen->update();
}

// Provisional function to use the classes
void map() {
   screen->erase();
   player.setAllAtributes(1, 1, 1, 1, 1, 1, 3);
   player.setImage("grand-knight");
   battle.setTerrain("grassland-r1", screen);
   battle.setHero(&player);
   loop(&drawMap);
   screen->draw("wesnoth", &background_pos);
   screen->draw("heroes-logo", &logo_pos);
   key[SDLK_ESCAPE] = 0;
}

void intro() {
   background_pos.x = 0;
   background_pos.y = 0;
   background_pos.w = 1024;
   background_pos.h = 768;

   logo_pos.x = 120;
   logo_pos.y = 120;
   logo_pos.w = 777;
   logo_pos.h = 385;

   screen->draw("wesnoth", &background_pos);
   screen->draw("heroes-logo", &logo_pos);
   mainMenu->draw(screen);
   screen->update();

   input.readInput();
   mouse = input.getMouse();
   key = input.getKeyboard();
   loop(&drawMenu);
}

int main(int argc, char *argv[]) {
   screen = new graphics;
   screen->newImage("wesnoth");
   screen->newImage("heroes-logo");
   screen->newImage("button");
   screen->newImage("button-active");
   screen->newImage("button-pressed");
   screen->newImage("grand-knight");
   screen->newImage("grassland-r1");
   screen->newImage("alpha", 50);
   background_pos.x = 500;
   background_pos.y = 500;
   background_pos.w = 108;
   background_pos.h = 22;
   mainMenu = new menu(screen, background_pos, &map, 1);
   intro();
   delete screen;
   delete mainMenu;

   return EXIT_SUCCESS;
}

/* Last Version: Jonan */
