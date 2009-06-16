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
/// The Menu class.
/// @author Jonan

#ifndef MENU_HPP
#define MENU_HPP

#include <deque>

#include <SDL/SDL.h>

#include "game_loop.hpp"

/// Controls a set of various Button classes as a group.
class Menu : public GameLoop{
  public:
    /// @param[in] position Top left hand corner of the menu.
    explicit Menu(SDL_Rect position); // Constructor
    ~Menu(void); // Destructor

    /// Activates the menu.
    void start(void) {loop();}

    /// Adds a new button to the menu.
    /// @param[in] text Text to be writen in the button.
    /// @param[in] function Function to execute when the button is pressed.
    void addButton(const char *text, void (&function)(void));

    /// Sets a background for the menu.
    /// From now on, the menu will call drawBackgroundFuntion()
    /// for drawing the background every time this is needed.
    /// @param[in] drawBackgroundFunction Funtion that draws the background.
    void setBackground(void (&drawBackgroundFunction)(void));

  private:
    class Button;

    // Draws the menu.
    void draw(void);

    // Funtion that will be called inside the loop
    virtual bool frame(void);

    SDL_Rect position; // Position of the top left hand corner of the menu.
    SDL_Surface *button_surface[3]; // The three button images.
    std::deque<Button*> buttons; // The buttons in the menu.
    int active_button; // Number of the button with the mouse over.
    int pressed_button; // Number of the button pressed.
    void (*drawBackgroundFunction)(void); // Function that draws the background.

    DISALLOW_COPY_AND_ASSIGN(Menu);
};

#endif // MENU_HPP
