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

/// @file
/// The timer class.
/// @author Jonan

#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL/SDL.h>

/// Controls the game's speed.
///
/// This class alows you to control the time
/// that passes bettwen to points of the program.
class timer {
   private:
      Uint32 now; // Actual time.
      Uint32 before; // The time it was the last time it looked.

   public:
      /// Indicates the starting point.
      ///
      /// The moment from which to start counting time. Make
      /// sure you call end(int) one time every time you use it.
      void start(void);
      /// Indicates the ending point.
      ///
      /// -no detailed description-
      ///
      /// @param[in] ms milliseconds that should pass bettwen the two points.
      void end(const int ms);
};

#endif // TIMER_HPP
