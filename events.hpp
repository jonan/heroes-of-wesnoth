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

/// @file
/// The events class and global events variables.
/// @author Jonan

#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SDL/SDL.h>

/// Number of keys in a keyboard
#define NUM_KEYS 323

// @{
/// Types of events
#define NO_EVENT    0
#define KEYBOARD    1
#define MOUSE       2
#define SYSTEM      3
// @}

// @{
/// Types of system events
#define QUIT        0
#define VIDEOEXPOSE 1
// @}

// @{
/// Mouse info
#define POSITION_X    0
#define POSITION_Y    1
#define BUTTON        2
// @}

// @{
/// Mouse buttons
#define NONE          0
#define LEFT          1
#define MIDDLE        2
#define RIGHT         3
#define UP            4
#define DOWN          5
// @}

/// Event control.
///
/// Tells you when has an event has occur. This event can be a system event (redimension,
/// close, redraw, etc.) or user event (keyboard or mouse). Once the event has occur,
/// gives you complete information about it.
class events {
   private:
      SDL_Event event;

   public:
      events(void); // Constructor
      ~events(void); // Destructor

      /// Reads the input from mouse, keyboard and system.
      ///
      /// Gets the input and stores the information obtained
      /// (must be called before any other events function).
      void readInput(void);
};

extern events *input;
extern bool *keys; // Stores the state of each keyboard key
extern int *mouse; // Mouse info

#endif // EVENTS_HPP
