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

#ifndef MENU_HPP
#define MENU_HPP

#include "graphics.hpp"

#define NORMAL  0
#define ACTIVE  1
#define PRESSED 2

class button {
   private:
      void (*function)(); // Function to execute when the button is pressed.
      bool active, pressed;
      char *text;
      int state; // Can be NORMAL, ACTIVE or PRESSED.

   public:
      button(void (*function)());
      ~button(void);

      int getState(void);
      void setState(int state);
      char *getText(void);
      void getFunction(void);
};

class menu {
   private:
      SDL_Rect position;
      bool background;
      SDL_Surface *buttonSurface[3]; // The three button images.
      button *buttons[]; // The buttons in the menu.
      graphics *screen;
      int numberButtons; // Number of buttons in the menu.
      int distance; // Distance between the buttons.
      int activeButton; // Number of the button with the mouse over.
      int pressedButton; // Number of the button pressed.


   public:
      menu(graphics *screen, SDL_Rect position, void (*function)(), int numberButtons, bool backgroud = true);
      ~menu(void);

      void moveMouse(int x, int y, bool pressed);
      void draw(graphics *screen);
};

#endif

/* Last Version: Jonan */
