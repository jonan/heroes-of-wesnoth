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
void startEngine(void) {
   srand( time(NULL) ); // Set seed for random numbers
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
   screen->newImage("alpha", 50);
   screen->newImage("armageddon");
   screen->newImage("bat-se-1");
   screen->newImage("bat-se-2");
   screen->newImage("bat-se-3");
   screen->newImage("bat-se-4");
   screen->newImage("bat-se-5");
   screen->newImage("blademaster");
   screen->newImage("button");
   screen->newImage("button-active");
   screen->newImage("button-pressed");
   screen->newImage("cavespider");
   screen->newImage("flanker");
   screen->newImage("floor");
   screen->newImage("floor2");
   screen->newImage("floor3");
   screen->newImage("floor4");
   screen->newImage("floor5");
   screen->newImage("floor6");
   screen->newImage("ford");
   screen->newImage("grand-knight");
   screen->newImage("grass-r1");
   screen->newImage("grass-r2");
   screen->newImage("grass-r3");
   screen->newImage("grass-r4");
   screen->newImage("grass-r5");
   screen->newImage("grass-r6");
   screen->newImage("grass-r7");
   screen->newImage("grass-r8");
   screen->newImage("heroes-logo");
   screen->newImage("pillager");
   screen->newImage("sergeant");
   screen->newImage("skeleton");
   screen->newImage("wesnoth");
   screen->newImage("wolf-rider");
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
