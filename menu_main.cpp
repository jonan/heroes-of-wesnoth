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
#include "boot.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "loop.hpp"
#include "menu.hpp"
#include "menu_main.hpp"

SDL_Rect background_pos, menu_pos, logo_pos;
menu *mainMenu;

// Set's all the position variables that the menu needs.
void setPositions(void) {
   menu_pos.x = 500;
   menu_pos.y = 500;
   menu_pos.w = 108;
   menu_pos.h = 22;

   background_pos.x = 0;
   background_pos.y = 0;
   background_pos.w = 1024;
   background_pos.h = 768;

   logo_pos.x = 120;
   logo_pos.y = 120;
   logo_pos.w = 777;
   logo_pos.h = 385;
}

// Draws the menu's background
void drawBackground(void) {
   screen->draw("wesnoth", background_pos);
   screen->draw("heroes-logo", logo_pos);
}

// Draws the menu.
bool drawMenu(void) {
   mainMenu->moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   mainMenu->draw();
   return false; // To continue in the loop.
}

// Free main menu
void deleteMenu(void) {
   delete mainMenu;
}

// Creates the menu.
void createMenu(void) {
   mainMenu = new menu(menu_pos, 2);
   mainMenu->setButton("Battle", createBattle);
   mainMenu->setButton("Quit", quit);
   mainMenu->addBackground(drawBackground);
   atexit(deleteMenu);
}

// Creates and starts the main menu.
void startMainMenu(void) {
   setPositions();
   createMenu();
   loop(drawMenu);
}
