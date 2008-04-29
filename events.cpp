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

#include "events.hpp"

// Constructor
events::events(void) {
   keys = new bool[NUM_KEYS];
   mouse = new int[3];

   // Set all keys to false
   for (int i = 0; i < NUM_KEYS; i++)
      keys[i] = false;
   // Clear mouse info
   for (int j = 0; j < 3; j++)
      mouse[j] = 0;

   // Mouse motion events won't go to the SDL queue
   SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
}

// Destructor
events::~events(void) {
   delete [] keys;
   delete [] mouse;
}

// Gets the input and stores the information obtained
// (must be called before any other events function).
void events::readInput(void) {
   SDL_GetMouseState(&mouse[POSITION_X], &mouse[POSITION_Y]);
   while (SDL_PollEvent(&event)) {
      // MOUSE
      if (event.type == SDL_MOUSEBUTTONDOWN) {
         if (event.button.button == SDL_BUTTON_LEFT)
            mouse[BUTTON] = LEFT;
         else if (event.button.button == SDL_BUTTON_MIDDLE)
            mouse[BUTTON] = MIDDLE;
         else if (event.button.button == SDL_BUTTON_RIGHT)
            mouse[BUTTON] = RIGHT;
      }
      else if (event.type == SDL_MOUSEBUTTONUP) {
         mouse[BUTTON] = NONE;
      }
      // KEYBOARD
      else if (event.type == SDL_KEYDOWN) {
         keys[event.key.keysym.sym] = true;
      }
      else if (event.type == SDL_KEYUP) {
         keys[event.key.keysym.sym] = false;
      }
   }
}

events *input = NULL;
bool *keys = NULL;
int *mouse = NULL;
