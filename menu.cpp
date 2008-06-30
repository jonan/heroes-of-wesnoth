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
button::button(const char *text, void (&function)(void)) {
   state = NORMAL;
   this->text = strdup(text);
   this->function = function;
}

// Destructor
button::~button(void) {
   free(text);
}

// ---End---

// class menu

// Constructor
menu::menu(SDL_Rect position) {
   this->position = position;

   // make sure the width and height are correct
   this->position.w = BUTTON_WIDTH;
   this->position.h = BUTTON_HEIGHT;

   buttonSurface[NORMAL] = screen->getImage("button");
   buttonSurface[ACTIVE] = screen->getImage("button-active");
   buttonSurface[PRESSED] = screen->getImage("button-pressed");

   activeButton = -1; //  The mouse is over no button.
   pressedButton = -1; //  No button is being pressed.
   background = false;
   drawBackground = false;
}

// Destructor
menu::~menu(void) {
   for (unsigned int i=0; i<buttons.size(); i++) {
      delete buttons[i];
   }
}

// Adds a new button to the menu.
void menu::addButton(const char *text, void (&function)(void)) {
   button *temp;
   temp = new button(text, function);
   buttons.push_back(temp);
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
void menu::moveMouse(const int x, const int y, const bool pressed) {
   bool mouseOver = false; // Indicates if the mouse is over a button

   if ( x>position.x && x < ( position.x + position.w ) ) { // Mouse in button's column
      int i = 0; // Buttons counter
      while ( i < (int) buttons.size() && !mouseOver ) {
         if ( y>position.y && y<(position.y+position.h) ) { // Mouse over the button
            mouseOver = true;
            if (pressed) {
               if (activeButton != -1) {
                  buttons[activeButton]->setState(NORMAL);
                  activeButton = -1;
               } else if (pressedButton != -1)
                  buttons[pressedButton]->setState(NORMAL);
               buttons[i]->setState(PRESSED);
               pressedButton = i;
            } else {
               if (pressedButton != -1) {
                  if (pressedButton == i) {
                     if (background) drawBackground = true;
                     buttons[i]->getFunction();
                  }
                  buttons[pressedButton]->setState(NORMAL);
                  pressedButton = -1;
               }
               if (activeButton != i) {
                  if (activeButton != -1) buttons[activeButton]->setState(NORMAL);
                  buttons[i]->setState(ACTIVE);
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
         buttons[activeButton]->setState(NORMAL);
         activeButton=-1;
      } else if (pressedButton != -1) {
         buttons[pressedButton]->setState(NORMAL);
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
   for (unsigned int i=0; i<buttons.size(); i++) {
      screen->draw( buttonSurface[ buttons[i]->getState() ], position );
      if (buttons[i]->getState() != PRESSED)
         screen->write(buttons[i]->getText() , position.x+28, position.y+3);
      else
         screen->write(buttons[i]->getText() , position.x+30, position.y+4);
      position.y += DISTANCE; // Set the position of the next button
   }
   // Put the position back to normal
   position.y -= (DISTANCE * buttons.size());
}

// ---End---
