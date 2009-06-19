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

#include "menu.hpp"

#include "events.hpp"
#include "graphics.hpp"

//events_engine
using events_engine::mouse;
using events_engine::MOUSE_X;
using events_engine::MOUSE_Y;
using events_engine::MOUSE_BUTTON;
// video_engine
using video_engine::screen;

const int DISTANCE = 30; // Distance between two buttons

const int BUTTON_WIDTH  = 108;
const int BUTTON_HEIGHT =  22;

enum {NORMAL, ACTIVE, PRESSED}; // Button states

// Class Button

// The characteristics of each menu button.
class Menu::Button {
  public:
    Button(const char *text, void (&function)(void)) : function(function), state(NORMAL) {this->text = strdup(text);} // Constructor
    ~Button(void) {free(text);} // Destructor

    char* getText     (void) {return text; }
    int   getState    (void) {return state;} // NORMAL, ACTIVE or PRESSED
    void  getFunction (void) {function();  }

    void setState(const int state) {this->state = state;}

  private:
    void (*function)(void); // Function to execute when the button is pressed.
    char *text; // Text to be writen in the button.
    int state; // Can be NORMAL, ACTIVE or PRESSED.

    DISALLOW_COPY_AND_ASSIGN(Button);
};

// ---End---

// Class Menu

// Constructor
Menu::Menu(SDL_Rect position) {
  this->position = position;

  // make sure the width and height are correct
  this->position.w = BUTTON_WIDTH;
  this->position.h = BUTTON_HEIGHT;

  button_surface[NORMAL] = screen->getImage("button");
  button_surface[ACTIVE] = screen->getImage("button-active");
  button_surface[PRESSED] = screen->getImage("button-pressed");

  active_button = -1; //  The mouse is over no button.
  pressed_button = -1; //  No button is being pressed.
  drawBackgroundFunction = NULL;
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
// for drawing the background every time this is needed.
void Menu::setBackground(void (&drawBackgroundFunction)(void)) {
  this->drawBackgroundFunction = drawBackgroundFunction;
}

// Draws the menu.
void Menu::draw(void) {
  if (drawBackgroundFunction) {
    screen->erase();
    drawBackgroundFunction();
  }

  for (unsigned int i=0; i<buttons.size(); i++) {
    screen->draw( button_surface[ buttons[i]->getState() ], position );
    if (buttons[i]->getState() != PRESSED)
      screen->writeCentered(buttons[i]->getText(),
                            position.x, position.x+BUTTON_WIDTH,
                            position.y, position.y+BUTTON_HEIGHT);
    else
      screen->writeCentered(buttons[i]->getText(),
                            position.x+2, position.x+BUTTON_WIDTH,
                            position.y+2, position.y+BUTTON_HEIGHT);
    position.y += DISTANCE; // Set the position of the next button
  }
  // Put the position back to normal
  position.y -= (DISTANCE * buttons.size());
}

// Funtion that will be called inside the loop
bool Menu::frame(void) {
  bool mouse_over = false; // Indicates if the mouse is over a button

  const int x = mouse[MOUSE_X];
  const int y = mouse[MOUSE_Y];

  if ( x>position.x && x < ( position.x + position.w ) ) { // Mouse in button's column
    int i = 0; // Buttons counter
    while ( i < static_cast<int>(buttons.size()) && !mouse_over ) {
      if ( y>position.y && y<(position.y+position.h) ) { // Mouse over the button
        mouse_over = true;
        if (mouse[MOUSE_BUTTON] == SDL_BUTTON_LEFT) {
          if (active_button != -1) {
            buttons[active_button]->setState(NORMAL);
            active_button = -1;
          } else if (pressed_button != -1)
            buttons[pressed_button]->setState(NORMAL);
          buttons[i]->setState(PRESSED);
          pressed_button = i;
        } else { // Mouse left button not pressed
          if (pressed_button != -1) {
            if (pressed_button == i)
              buttons[i]->getFunction();
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

  draw();

  return false;
}

// ---End---
