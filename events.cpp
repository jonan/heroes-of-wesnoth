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

#include "events.hpp"

#include "graphics.hpp"

using video_engine::screen;
using video_engine::OPAQUE;
using video_engine::NONE;

namespace events_engine {

// Singleton pattern constructor
Events* Events::instance(void) {
  static Events inst;
  return &inst;
}

// Destructor
Events::~Events(void) {
  delete [] keys;
  delete [] mouse;
}

// Gets the input and stores the information obtained
// (must be called before any other events function).
void Events::readInput(void) {
  SDL_GetMouseState(&mouse[POSITION_X], &mouse[POSITION_Y]);
  while (SDL_PollEvent(&event)) {
    // MOUSE
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      if (event.button.button == SDL_BUTTON_LEFT)
        mouse[BUTTON] = BUTTON_LEFT;
      else if (event.button.button == SDL_BUTTON_MIDDLE)
        mouse[BUTTON] = BUTTON_MIDDLE;
      else if (event.button.button == SDL_BUTTON_RIGHT)
        mouse[BUTTON] = BUTTON_RIGHT;
      else if (event.button.button == SDL_BUTTON_WHEELUP)
        mouse[BUTTON] = WHEEL_UP;
      else if (event.button.button == SDL_BUTTON_WHEELDOWN)
        mouse[BUTTON] = WHEEL_DOWN;
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
      if (mouse[BUTTON] != WHEEL_UP && mouse[BUTTON] != WHEEL_DOWN)
        mouse[BUTTON] = NONE;
    }
    // KEYBOARD
    else if (event.type == SDL_KEYDOWN) {
      keys[event.key.keysym.sym] = true;
    }
    else if (event.type == SDL_KEYUP) {
      keys[event.key.keysym.sym] = false;
    }
    // RESIZE
    else if (event.type == SDL_VIDEORESIZE) {
      screen->resize(event.resize.w, event.resize.h);
    }
  }
}

// It's called every time the screen is updated,
// so it should only be called from graphics.
void Events::drawMouse(void) {
  SDL_Rect position;
  position.x = mouse[POSITION_X];
  position.y = mouse[POSITION_Y];
  screen->draw(cursor_image[cursor_type], position);
}

// Constructor
Events::Events(void) {
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
  // Hide default cursor
  SDL_ShowCursor(SDL_DISABLE);

  // Set the cursor's images
  cursor_image[NORMAL] = screen->getImage("cursors/normal", OPAQUE, NONE, 0);
  cursor_image[ATTACK] = screen->getImage("cursors/attack", OPAQUE, NONE, 0);
  cursor_image[MOVE] = screen->getImage("cursors/move", OPAQUE, NONE, 0);
  cursor_image[ILLEGAL] = screen->getImage("cursors/select-illegal", OPAQUE, NONE, 0);
  cursor_image[WAIT] = screen->getImage("cursors/wait", OPAQUE, NONE, 0);

  cursor_type = NORMAL;
}

Events *input = NULL;
bool *keys = NULL;
int *mouse = NULL;

} // namespace events_engine
