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

#include "boot.hpp"
#include "events.hpp"
#include "graphics.hpp"

// Loads the engine's global objects.
void startEngine(void) {
   screen = new graphics;
   input = new events;
}

// Frees the engine's global objects.
void freeEngine(void) {
   delete input;
   delete screen;
}

// Loads the images that will be used almost every
// time the game is executed.
void loadMainImages(void) {
   screen->newImage("wesnoth");
   screen->newImage("heroes-logo");
   screen->newImage("skeleton");
   screen->newImage("button");
   screen->newImage("button-active");
   screen->newImage("button-pressed");
   screen->newImage("grand-knight");
   screen->newImage("grassland-r1");
   screen->newImage("alpha", 50);
}

// Starts the engine and loads the main images.
void boot(void) {
   startEngine();
   atexit(freeEngine);
   loadMainImages();
}

// Exits the game.
void quit(void) {
   exit(EXIT_SUCCESS);
}
