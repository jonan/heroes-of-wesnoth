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

#include "boot.hpp"

#include <ctime>
#include <cstdlib>

#include "events.hpp"
#include "graphics.hpp"

// events_engine
using events_engine::input;

// video_engine
using video_engine::screen;

using video_engine::OPAQUE;

using video_engine::NONE;

// Loads the engine's global objects.
void startEngine(const bool fullscreen, const int width, const int height) {
  srand( time(NULL) ); // Set seed for random numbers
  screen = video_engine::Graphics::instance(fullscreen, width, height);
  input = events_engine::Events::instance();
}

// Loads the images that will be used almost every
// time the game is executed.
void loadMainImages(void) {
  screen->newImage("alpha", 50, NONE, 0);
  screen->newImage("button", OPAQUE, NONE, 0);
  screen->newImage("button-active", OPAQUE, NONE, 0);
  screen->newImage("button-pressed", OPAQUE, NONE, 0);
  screen->newImage("heroes-logo", OPAQUE, NONE, 0);
  screen->newImage("wesnoth", OPAQUE, NONE, 0);
  // Images to soften terrains.
  // They are always loaded and it shouldn't be like that,
  // but until that is fixed, better loading them at boot time.
}

// Starts the engine and loads the main images.
void boot(const bool fullscreen, const int width, const int height) {
  startEngine(fullscreen, width, height);
  loadMainImages();
}

// Exits the game.
void quit(void) {
  exit(EXIT_SUCCESS);
}
