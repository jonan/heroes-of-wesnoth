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

#include "timer.hpp"

// Constructor
Timer::Timer(void) {
  start();
}

// The moment from which to start counting time. Make
// sure you call endFPS(int) one time every time you use it.
void Timer::start(void) {
  now = before = SDL_GetTicks();
}

// Indicates the ending point.
void Timer::end(const Uint32 ms) {
  now = SDL_GetTicks();

  if ( (now-before) < ms )
    SDL_Delay( ms - (now - before) );
}
