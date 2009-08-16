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

#include "menu_main.hpp"

#include "battle.hpp"
#include "boot.hpp"
#include "editor.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "menu.hpp"
#include "mission.hpp"

//events_engine
using events_engine::mouse;
using events_engine::MOUSE_X;
using events_engine::MOUSE_Y;
using events_engine::MOUSE_BUTTON;
// video_engine
using video_engine::screen;

SDL_Rect background_pos, menu_pos, logo_pos;
Menu *main_menu;

// Set's all the position variables that the menu needs.
void setPositions(void) {
  menu_pos.x = 465;
  menu_pos.y = 500;
  menu_pos.w = 108;
  menu_pos.h = 22;

  background_pos.x = 0;
  background_pos.y = 0;
  background_pos.w = 1024;
  background_pos.h = 768;

  logo_pos.x = 120;
  logo_pos.y = 70;
  logo_pos.w = 777;
  logo_pos.h = 385;
}

// Draws the menu's background
void drawBackground(void) {
  screen->draw("wesnoth", background_pos);
  screen->draw("heroes-logo", logo_pos);
  screen->write("Development Version", 860, 740);
}

// Creates the menu.
void createMenu(void) {
  main_menu = new Menu(menu_pos);
  main_menu->addButton("Mission 1", mission1);
  main_menu->addButton("Mission 2", mission2);
  main_menu->addButton("Mission 3", mission3);
  main_menu->addButton("Battle", createDefaultBattle);
  main_menu->addButton("Editor", startEditor);
  main_menu->addButton("Quit", quit);
  main_menu->setBackground(drawBackground);
}

// Creates and starts the main menu.
void startMainMenu(void) {
  setPositions();
  createMenu();
  main_menu->start();
  delete main_menu;
}
