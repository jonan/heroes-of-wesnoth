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

#include "events.hpp"

#include "graphics.hpp"

using video_engine::screen;

namespace events_engine {

// Singleton pattern constructor
Events* Events::getInstance(void) {
  static Events instance;
  return &instance;
}

// Destructor
Events::~Events(void) {
  delete event;
  delete mouse_position;
  delete [] keys;
  delete [] mouse;
}

// Gets the input and stores the information obtained
// (must be called before any other events function).
void Events::readInput(void) {
  SDL_GetMouseState(&mouse[POSITION_X], &mouse[POSITION_Y]);
  while (SDL_PollEvent(event)) {
    switch (event->type) {
      case SDL_MOUSEBUTTONDOWN:
        mouse[BUTTON] = event->button.button;
        break;
      case SDL_MOUSEBUTTONUP:
        if (mouse[BUTTON] != SDL_BUTTON_WHEELUP && mouse[BUTTON] != SDL_BUTTON_WHEELDOWN)
          mouse[BUTTON] = 0;
        break;
      case SDL_KEYDOWN:
        keys[event->key.keysym.sym] = true;
        break;
      case SDL_KEYUP:
        keys[event->key.keysym.sym] = false;
        break;
      case SDL_VIDEORESIZE:
        screen->resize(event->resize.w, event->resize.h);
        break;
      default:
        // Nothing to do
        break;
    }
  }
}

// It's called every time the screen is updated,
// so it should only be called from graphics.
void Events::drawMouse(void) {
  if (cursor_type != NO_CURSOR) {
    mouse_position->x = mouse[POSITION_X];
    mouse_position->y = mouse[POSITION_Y];
    screen->draw(cursor_image[cursor_type], *mouse_position);
  }
}

// Constructor
Events::Events(void) {
  keys = new bool[SDLK_LAST];
  mouse = new int[3];

  // Set all keys to false
  for (int i = 0; i < SDLK_LAST; i++)
    keys[i] = false;
  // Clear mouse info
  for (int j = 0; j < 3; j++)
    mouse[j] = 0;

  // Mouse motion events won't go to the SDL queue
  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
  // Hide default cursor
  SDL_ShowCursor(SDL_DISABLE);

  event = new SDL_Event;
  mouse_position = new SDL_Rect;

  // Set the cursor's images
  cursor_image[NORMAL] = screen->getImage("cursors/normal");
  cursor_image[ATTACK] = screen->getImage("cursors/attack");
  cursor_image[MOVE] = screen->getImage("cursors/move");
  cursor_image[ILLEGAL] = screen->getImage("cursors/select-illegal");
  cursor_image[WAIT] = screen->getImage("cursors/wait");

  cursor_type = NORMAL;
}

Events *input = NULL;

bool *keys = NULL;
int *mouse = NULL;

} // namespace events_engine
