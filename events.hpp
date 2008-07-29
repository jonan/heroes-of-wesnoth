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

#include "macros.hpp"

/// All functions related to events.
///
/// -no detailed description-
namespace events_engine {

/// Mouse info
enum {POSITION_X, POSITION_Y, BUTTON};

/// Mouse buttons
enum {NONE, BUTTON_LEFT, BUTTON_MIDDLE, BUTTON_RIGHT, WHEEL_UP, WHEEL_DOWN};

/// Event control.
///
/// Tells you when has an event has occur. This event can be a system event (redimension,
/// close, redraw, etc.) or user event (keyboard or mouse). Once the event has occur,
/// gives you complete information about it.
class Events {
  public:
    static Events* instance(void); // Singleton pattern constructor
    ~Events(void); // Destructor

    /// Reads the input from mouse, keyboard and system.
    ///
    /// Gets the input and stores the information obtained
    /// (must be called before any other events function).
    void readInput(void);

  private:
    static const int NUM_KEYS = 323;

    Events(void); // Constructor

    SDL_Event event;

    DISALLOW_COPY_AND_ASSIGN(Events);
};

extern Events *input;
extern bool *keys; // Stores the state of each keyboard key
extern int *mouse; // Mouse info

} // namespace events_engine

#endif // EVENTS_HPP
