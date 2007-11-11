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

#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SDL/SDL.h>

/// Types of events
#define NO_EVENT    0
#define KEYBOARD    1
#define MOUSE       2
#define SYSTEM      3
/// Types of system events
#define QUIT        0
#define VIDEOEXPOSE 1
/// Mouse info
#define POSITION_X    0
#define POSITION_Y    1
#define LEFT_BUTTON   2
#define MIDDLE_BUTTON 3
#define RIGHT_BUTTON  4

/// Event control.
///
/// Tells you when has an event has occur. This event can be a system event (redimension,
/// close, redraw, etc.) or user event (keyboard or mouse). Once the event has occur,
/// gives you complete information about it.
class events {
   private:
      SDL_Event event;
      bool keys[323];
      int mouse[5];
      int type; // Can be KEYBOARD, MOUSE, SYSTEM or NO_EVENT
      int systemType; // Can be QUIT or VIDEOEXPOSE

   public:
      events(void); // Constructor

      /// Reads the input from mouse, keyboard and system.
      ///
      /// Gets the input and stores the information obtained
      /// (must be called before any other events function).
      void readInput(void);
      /// Returns the keyboard layout.
      ///
      /// Returns an array of the 323 keys with their
      /// pressed value, TRUE or FALSE.
      bool* getKeyboard(void);
      /// Returns the mouse state and position.
      ///
      /// Returns a size 5 array with the mouse info: POSITION_X,
      /// POSITION_Y, LEFT_BUTTON, MIDDLE_BUTTON and RIGHT_BUTTON.
      /// The button referred infos may be 1 (pressed) or 0 (not pressed).
      int* getMouse(void);
      /// Returns the type of event occurred.
      ///
      /// Returns the type of event: KEYBOARD, MOUSE, SYSTEM or NO_EVENT.
      int getType(void);
      /// Returns the system type of event occurred.
      ///
      /// When getType() returns SYSTEM check if it's QUIT or VIDEOEXPOSE.
      /// Must only be called after getType() has returned SYSTEM.
      int getSystemType(void);
};

#endif

/* Last Version: Jonan */
