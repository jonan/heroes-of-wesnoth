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

#include <ctime>
#include <cstdlib>

#include "boot.hpp"
#include "events.hpp"
#include "graphics.hpp"

// Loads the engine's global objects.
void startEngine(const bool fullscreen, const screenFormat scrFrmt) {

   srand( time(NULL) ); // Set seed for random numbers
   screen = new graphics(fullscreen, scrFrmt);
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
   screen->newImage("alpha", 50);
   screen->newImage("button");
   screen->newImage("button-active");
   screen->newImage("button-pressed");
   screen->newImage("heroes-logo");
   screen->newImage("wesnoth");
}

// Starts the engine and loads the main images.
void boot(const bool fullscreen, const int width, const int height, const int bpp) {
   const screenFormat scrFrmt = { width, height, bpp };
   startEngine(fullscreen, scrFrmt);
   atexit(freeEngine);
   loadMainImages();
}

// Exits the game.
void quit(void) {
   exit(EXIT_SUCCESS);
}
