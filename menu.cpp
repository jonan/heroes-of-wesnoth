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

#include "menu.hpp"

// class button

// Constructor
button::button(const char *text, void (*function)()) {
   this->text = new char [strlen(text)];

   this->function = function;
   state = NORMAL;
   strcpy(this->text, text);

   next = NULL;
}

// Destructor
button::~button(void) {
   delete text;
}

// Returns the button's state.
int button::getState(void) {
   return state;
}

// Changes the button state.
void button::setState(const int state) {
   this->state=state;
}

// Returns the button's text.
char *button::getText(void) {
   return text;
}

// Returns the button's function.
void button::getFunction(void) {
   function();
}

// ---End---

// class menu

// Constructor
menu::menu(graphics *screen, SDL_Rect position, void (*function)(), int numberButtons, bool backgroud) {
   this->screen = screen;
   this->position = position;
   this->numberButtons = numberButtons;
   this->background = background;

   buttonSurface[NORMAL] = this->screen->getImage("button");
   buttonSurface[ACTIVE] = this->screen->getImage("button-active");
   buttonSurface[PRESSED] = this->screen->getImage("button-pressed");

   buttons[numberButtons-1] = new button("Battle", function);
   for (int i=1; i<numberButtons; i++) {
      
   }
   distance = 30;
   activeButton = -1; //  The mouse is over no button.
   pressedButton = -1; //  No button is being pressed.
}

// Destructor
menu::~menu(void) {
   for (int i=0; i<numberButtons; i++)
      delete buttons[i];
}

// Every time the mouse's position or the mouse's buttons change, this
// function should be called so the menu knows which button is being pressed.
void menu::moveMouse(int x, int y, int pressed) {
   if // Mouse over button
   (
   x>position.x                &&
   x < (position.x+position.w) &&
   y>position.y                &&
   y < (position.y+position.h)
   ) {
      if (pressed==1 && activeButton==0 ) {
      buttons[0]->setState(PRESSED);
      pressedButton = 0;
      }
      else {
         if (pressedButton==0) buttons[0]->getFunction();
         buttons[0]->setState(ACTIVE);
         activeButton = 0;
         }
      }
   else // Mouse not over button
      if (activeButton != -1) {
         buttons[activeButton]->setState(NORMAL);
         activeButton=-1;
         pressedButton=-1;
      }
}

// Draws the menu.
void menu::draw(graphics *screen) {
   for (int i=0; i<numberButtons; i++) {
      screen->draw( buttonSurface[ buttons[i]->getState() ], &position );
      if (buttons[i]->getState() != PRESSED)
         screen->write(buttons[i]->getText() , position.x+32, position.y+3);
      else
         screen->write(buttons[i]->getText() , position.x+34, position.y+4);
      position.y += distance; // Set the position of the next button
   }
   // Put the position back to normal
   position.y -= (distance * numberButtons);
}

/// @todo Create the function
// Every time the function is called, sets the attributes
// to each button until all button classes have been set.
// (Should be called immediately after the constructor and
// as may times as button classes are there in the menu)
void menu::setButton(const char *text, void (*function)()) {

}

// ---End---

/* Last Version: Jonan */
