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

#include "menu.hpp"

#include "graphics.hpp"

// video_engine
using video_engine::screen;

using video_engine::OPAQUE;

using video_engine::NONE;

const int DISTANCE = 30; // Distance between two buttons

const int BUTTON_WIDTH  = 108;
const int BUTTON_HEIGHT =  22;

enum {NORMAL, ACTIVE, PRESSED}; // Button states

// class button

// Constructor
Button::Button(const char *text, void (&function)(void)) {
  state = NORMAL;
  this->text = strdup(text);
  this->function = function;
}

// Destructor
Button::~Button(void) {
  free(text);
}

// ---End---

// class menu

// Constructor
Menu::Menu(SDL_Rect position) {
  this->position = position;

  // make sure the width and height are correct
  this->position.w = BUTTON_WIDTH;
  this->position.h = BUTTON_HEIGHT;

  button_surface[NORMAL] = screen->getImage("button", OPAQUE, NONE, 0);
  button_surface[ACTIVE] = screen->getImage("button-active", OPAQUE, NONE, 0);
  button_surface[PRESSED] = screen->getImage("button-pressed", OPAQUE, NONE, 0);

  active_button = -1; //  The mouse is over no button.
  pressed_button = -1; //  No button is being pressed.
  background = false;
  draw_background = false;
}

// Destructor
Menu::~Menu(void) {
  for (unsigned int i=0; i<buttons.size(); i++) {
    delete buttons[i];
  }
}

// Adds a new button to the menu.
void Menu::addButton(const char *text, void (&function)(void)) {
  Button *temp;
  temp = new Button(text, function);
  buttons.push_back(temp);
}

// From now on, the menu will call drawBackgroundFuntion()
// for drawing the menu every time this is needed.
void Menu::addBackground(void (&drawBackgroundFunction)(void)) {
  background = true;
  draw_background = true;
  this->drawBackgroundFunction = drawBackgroundFunction;
}

// Every time the mouse's position or the mouse's buttons change, this
// function should be called so the menu knows which button is being pressed.
void Menu::moveMouse(const int x, const int y, const bool pressed) {
  bool mouse_over = false; // Indicates if the mouse is over a button

  if ( x>position.x && x < ( position.x + position.w ) ) { // Mouse in button's column
    int i = 0; // Buttons counter
    while ( i < static_cast<int>(buttons.size()) && !mouse_over ) {
      if ( y>position.y && y<(position.y+position.h) ) { // Mouse over the button
        mouse_over = true;
        if (pressed) {
          if (active_button != -1) {
            buttons[active_button]->setState(NORMAL);
            active_button = -1;
          } else if (pressed_button != -1)
            buttons[pressed_button]->setState(NORMAL);
          buttons[i]->setState(PRESSED);
          pressed_button = i;
        } else {
          if (pressed_button != -1) {
            if (pressed_button == i) {
              if (background) draw_background = true;
              buttons[i]->getFunction();
            }
            buttons[pressed_button]->setState(NORMAL);
            pressed_button = -1;
          }
          if (active_button != i) {
            if (active_button != -1) buttons[active_button]->setState(NORMAL);
            buttons[i]->setState(ACTIVE);
            active_button = i;
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

  if (!mouse_over) { // Mouse over no button
    if (active_button != -1) {
      buttons[active_button]->setState(NORMAL);
      active_button=-1;
    } else if (pressed_button != -1) {
      buttons[pressed_button]->setState(NORMAL);
      pressed_button=-1;
    }
  }
}

// Draws the menu.
void Menu::draw(void) {
  if (draw_background) {
    drawBackgroundFunction();
    draw_background = false;
  }
  for (unsigned int i=0; i<buttons.size(); i++) {
    screen->draw( button_surface[ buttons[i]->getState() ], position );
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
