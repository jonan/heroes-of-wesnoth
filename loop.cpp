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

#include "loop.hpp"

#include "events.hpp"
#include "graphics.hpp"
#include "timer.hpp"

// events_engine
using events_engine::input;
// video_engine
using video_engine::screen;

// Constructor
GameLoop::GameLoop(void) {
  fps = new Timer;
}

// Destructor
GameLoop::~GameLoop(void) {
  delete fps;
}

// Starts the loop
void GameLoop::loop(void) {
  done = false;

  while (!done) {
    fps->start();
    input->readInput();
    done = frame();
    screen->update();
    fps->end(30);
  }
}

// This function is deprecate and will be erased
// as soon as all code depending on it is updated.
void loop(bool (&function)(void)) {
  bool done = false;
  Timer fps;

  while (!done) {
    fps.start();
    input->readInput();
    done = function();
    screen->update();
    fps.end(30);
  }
}
