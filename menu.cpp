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

#include "graphics.hpp"
#include "menu.hpp"

// class button

// Constructor
button::button(void) {
   state = NORMAL;
}

// Destructor
button::~button(void) {
   delete [] text;
}

// Returns the button's text.
char* button::getText(void) {
   return text;
}

// Executes the button's function.
void button::getFunction(void) {
   function();
}

// Returns the button's state.
int button::getState(void) {
   return state;
}

// Changes all the button's attributes.
void button::setAttributes(const char *text, void (&function)(void)) {
   this->text = strdup(text);
   this->function = function;
}

// Changes the button state.
void button::setState(const int state) {
   this->state=state;
}

// ---End---

// class menu

// Constructor
menu::menu(SDL_Rect position, int numberButtons) {
   this->position = position;
   buttons = new button[numberButtons];
   this->numberButtons = numberButtons;

   // make sure the width and height are correct
   this->position.w = BUTTON_WIDTH;
   this->position.h = BUTTON_HEIGHT;

   buttonSurface[NORMAL] = screen->getImage("button");
   buttonSurface[ACTIVE] = screen->getImage("button-active");
   buttonSurface[PRESSED] = screen->getImage("button-pressed");

   buttonsCreated = 0;
   activeButton = -1; //  The mouse is over no button.
   pressedButton = -1; //  No button is being pressed.
   background = false;
   drawBackground = false;
}

// Destructor
menu::~menu(void) {
   delete [] buttons;
}

// Every time the function is called, sets the attributes
// to each button until all button classes have been set.
// (Should be called immediately after the constructor and
// as may times as button classes are there in the menu)
void menu::setButton(const char *text, void (&function)(void)) {
   if (buttonsCreated < numberButtons) {
      buttons[buttonsCreated].setAttributes(text, function);
      buttonsCreated++;
   }
}

// From now on, the menu will call drawBackgroundFuntion()
// for drawing the menu every time this is needed.
void menu::addBackground(void (&drawBackgroundFunction)(void)) {
   background = true;
   drawBackground = true;
   this->drawBackgroundFunction = drawBackgroundFunction;
}

// Every time the mouse's position or the mouse's buttons change, this
// function should be called so the menu knows which button is being pressed.
void menu::moveMouse(const int x, const int y, const int pressed) {
   bool mouseOver = false; // Indicates if the mouse is over a button

   if ( x>position.x && x < ( position.x + position.w ) ) { // Mouse in button's column
      int i = 0; // Buttons counter
      while ( i<numberButtons && !mouseOver ) {
         if ( y>position.y && y<(position.y+position.h) ) { // Mouse over the button
            mouseOver = true;
            if ( pressed == SDL_BUTTON_LEFT ) {
               if (activeButton != -1) {
                  buttons[activeButton].setState(NORMAL);
                  activeButton = -1;
               } else if (pressedButton != -1)
                  buttons[pressedButton].setState(NORMAL);
               buttons[i].setState(PRESSED);
               pressedButton = i;
            } else {
               if (pressedButton != -1) {
                  if (pressedButton == i) {
                     if (background) drawBackground = true;
                     buttons[i].getFunction();
                  }
                  buttons[pressedButton].setState(NORMAL);
                  pressedButton = -1;
               }
               if (activeButton != i) {
                  if (activeButton != -1) buttons[activeButton].setState(NORMAL);
                  buttons[i].setState(ACTIVE);
                  activeButton = i;
               }
            }
         } else { // See if the mouse is over the next button
            position.y += DISTANCE;
            i++;
         }
      }
      // put position back to normal
      position.y -= (DISTANCE*i);
   }

   if (!mouseOver) { // Mouse over no button
      if (activeButton != -1) {
         buttons[activeButton].setState(NORMAL);
         activeButton=-1;
      } else if (pressedButton != -1) {
         buttons[pressedButton].setState(NORMAL);
         pressedButton=-1;
      }
   }
}

// Draws the menu.
void menu::draw(void) {
   if (drawBackground) {
      drawBackgroundFunction();
      drawBackground = false;
   }
   for (int i=0; i<numberButtons; i++) {
      screen->draw( buttonSurface[ buttons[i].getState() ], position );
      if (buttons[i].getState() != PRESSED)
         screen->write(buttons[i].getText() , position.x+32, position.y+3);
      else
         screen->write(buttons[i].getText() , position.x+34, position.y+4);
      position.y += DISTANCE; // Set the position of the next button
   }
   // Put the position back to normal
   position.y -= (DISTANCE * numberButtons);
}

// ---End---
