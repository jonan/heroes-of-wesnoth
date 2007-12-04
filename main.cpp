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

SDL_Rect background_pos;
SDL_Rect logo_pos;
SDL_Surface *wesnoth;
SDL_Surface *logo;

hero player("magician");
menu *mainMenu;
map battle;
graphics *screen;
events input;
bool* key;
int* mouse;
int done;

void loop() {
   done=0;

   while (done == 0) {
      input.readInput();
      mouse = input.getMouse();
      key = input.getKeyboard();
      if (key[SDLK_ESCAPE]) {done = 1;}
      if (input.getType() == SYSTEM)
         if (input.getSystemType() == QUIT)
            done = 1;
   }
}

Uint32 drawBattle(Uint32 interval, void *param){
   printf("Draw Battle\n");
   battle.moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[LEFT_BUTTON]);
   battle.draw(screen);
   screen->update();

   return interval;
}

Uint32 drawMenu(Uint32 interval, void *param) {
   //printf("Draw Menu\n");
   /*screen->draw("wesnoth", &background_pos);
   screen->draw("heroes-logo", &logo_pos);
   screen->write("XXXXXXXXXX", mouse[POSITION_X], mouse[POSITION_Y]);*/
   mainMenu->moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[LEFT_BUTTON]);
   mainMenu->draw(screen);
   screen->update();

   return interval;
}

// Provisional function to use the classes
void map() {
   screen->newImage("grand-knight");
   screen->newImage("grassland-r1");
   screen->newImage("alpha", 50);
   player.setAllAtributes(1, 1, 1, 1, 1, 1, 3);
   player.setImage("grand-knight");
   battle.setTerrain("grassland-r1", screen);
   battle.setHero(&player);
   screen->execute(drawBattle);
   loop();
   screen->execute(drawMenu);
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
   SDL_Delay(100);

   done=0;
   input.readInput();
   mouse = input.getMouse();
   key = input.getKeyboard();
   screen->execute(drawMenu);

   loop();
}

int main(int argc, char *argv[]) {
   screen = new graphics;
   screen->newImage("wesnoth");
   screen->newImage("heroes-logo");
   screen->newImage("button");
   screen->newImage("button-active");
   screen->newImage("button-pressed");
   background_pos.x = 500;
   background_pos.y = 500;
   background_pos.w = 108;
   background_pos.h = 22;
   mainMenu = new menu(screen, background_pos, &map, 1);
   //intro();
   map();
   delete screen;
   delete mainMenu;

   return EXIT_SUCCESS;
}

/* Last Version: Jonan */
