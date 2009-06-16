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

/// @file
/// The Timer class.
/// @author Jonan

#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL/SDL.h>

#include "macros.hpp"

/// Controls the game's speed.
/// This class alows you to control the time
/// that passes between to points of the program.
class Timer {
  public:
    Timer(void) {} // Constructor

    /// Indicates the starting point.
    /// The moment from which to start counting time. Make
    /// sure you call end() one time every time you use it.
    void start(void) {
      now = before = SDL_GetTicks();
    }
    /// Indicates the ending point.
    /// @param[in] ms milliseconds that should pass between the two points.
    void end(const Uint32 ms) {
      now = SDL_GetTicks();
      difference = now - before;
      if (difference < ms)
        SDL_Delay(ms - difference);
    }

  private:
    Uint32 now; // Actual time.
    Uint32 before; // The time it was the last time it looked.
    Uint32 difference;

    DISALLOW_COPY_AND_ASSIGN(Timer);
};

#endif // TIMER_HPP
