/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007-2008 Jon Ander Peñalba <jonan88@gmail.com>

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

#include "loop.hpp"

#include "events.hpp"
#include "graphics.hpp"
#include "timer.hpp"

// events_engine
using events_engine::input;
// video_engine
using video_engine::screen;

// Controls a general game loop.
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
