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

#include "events.hpp"

// Constructor
events::events(void) {
   type = NO_EVENT;

   // Set all keys to false
   for (int i = 0; i < NUM_KEYS; i++)
      keys[i] = false;
   // Clear mouse info
   for (int j = 0; j < 5; j++)
      mouse[j] = 0;
}

// Gets the input and stores the information obtained
// (must be called before any other events function).
void events::readInput(void) {
   SDL_WaitEvent(&event);
      // MOUSE
      if (event.type == SDL_MOUSEMOTION) {
         mouse[POSITION_X] = event.motion.x;
         mouse[POSITION_Y] = event.motion.y;
         type = MOUSE;
      }
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
         if (event.button.button == SDL_BUTTON_LEFT)
            mouse[LEFT_BUTTON] = 1;
         else if (event.button.button == SDL_BUTTON_MIDDLE)
            mouse[MIDDLE_BUTTON] = 1;
         else if (event.button.button == SDL_BUTTON_RIGHT)
            mouse[RIGHT_BUTTON] = 1;
         type = MOUSE;
      }
      else if (event.type == SDL_MOUSEBUTTONUP) {
         if (event.button.button == SDL_BUTTON_LEFT)
            mouse[LEFT_BUTTON] = 0;
         else if (event.button.button == SDL_BUTTON_MIDDLE)
            mouse[MIDDLE_BUTTON] = 0;
         else if (event.button.button == SDL_BUTTON_RIGHT)
            mouse[RIGHT_BUTTON] = 0;
         type = MOUSE;
      }
      // KEYBOARD
      else if (event.type == SDL_KEYDOWN) {
         keys[event.key.keysym.sym] = true;
         type = KEYBOARD;
      }
      else if (event.type == SDL_KEYUP) {
         keys[event.key.keysym.sym] = false;
         type = KEYBOARD;
      }
      // SYSTEM
      else if (event.type == SDL_VIDEOEXPOSE) {
         systemType = VIDEOEXPOSE;
         type = SYSTEM;
      }
      else if (event.type == SDL_QUIT) {
         systemType = QUIT;
         type = SYSTEM;
      }
}

// Returns an array of the keyboard keys with their
// pressed value, TRUE or FALSE.
bool* events::getKeyboard(void) {
      return keys;
}

// Returns a size 5 array with the mouse info: POSITION_X,
// POSITION_Y, LEFT_BUTTON, MIDDLE_BUTTON and RIGHT_BUTTON.
// The button referred infos may be 1 (pressed) or 0 (not pressed).
int* events::getMouse(void) {
      return mouse;
}

// Returns KEYBOARD, MOUSE, SYSTEM or NO_EVENT.
int events::getType(void) {
      return type;
}

// When getType() returns SYSTEM check if it's QUIT or VIDEOEXPOSE.
// Must only be called after getType() has returned SYSTEM.
int events::getSystemType(void) {
      return systemType;
}

/* Last Version: Jonan */
