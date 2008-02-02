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

#include <iostream>

#include "graphics.hpp"

using namespace std;

// Initializes SDL, SDL_ttf and SDL_mixer
void graphics::init(void) {
   cout << "Starting SDL...\t\t\t\t";
   if ( SDL_Init (SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0 ) { // SDL_INIT_AUDIO not yet needed
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   }
   atexit(SDL_Quit);
   cout << "[ ok ]\n";
   cout << "Starting SDL_ttf...\t\t\t";
   if ( TTF_Init() < 0 ) {
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   }
   atexit(TTF_Quit);
   cout << "[ ok ]\n";
}

// Creates the surface that will be drawn directly to the screen
void graphics::createWindow(void) {
   cout << "Opening " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << " window...\t\t";
   SDL_WM_SetCaption ("Heroes of Wesnoth", NULL);
   // Not using fullscreen to prevent reseting computer after program crash.
   // This will change in final version.
   screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, BPP, SDL_DOUBLEBUF | SDL_ANYFORMAT);// | SDL_FULLSCREEN);
   if (screen == NULL) {
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   }
   cout << "[ ok ]\n";
}

// Constructor
graphics::graphics(void) {
   init();
   createWindow();
   image = new imageList;
   text = new ttf();
   timerID = 0;
}

// Destructor
graphics::~graphics(void) {
   cout << "Freeing screen...\n";
   if (timerID != 0) SDL_RemoveTimer(timerID);
   delete image;
   delete text;
   SDL_FreeSurface(screen);
}

// Adds a new image to the list
void graphics::newImage(const char *imageName, const int alpha) {
   image->addImage(imageName, alpha);
}

// Returns the surface of a preveously loaded image.
SDL_Surface* graphics::getImage(const char *imageName) {
   SDL_Surface *temp;

   temp = image->getSurface(imageName);
   return temp;
}

// Draws an image previously loaded to the indicated position.
void graphics::draw(const char *imageName, SDL_Rect *position) {
   SDL_Surface *temp;

   temp = image->getSurface(imageName);
   SDL_BlitSurface(temp, NULL, screen, position);
}

// Draws a surface to the indicated position.
void graphics::draw(SDL_Surface *img, SDL_Rect *position) {
   SDL_BlitSurface(img, NULL, screen, position);
}

// Puts the screen in black.
void graphics::erase(void) {
   SDL_FillRect(screen, NULL, 0);
}

// Writes text in the screen.
void graphics::write(const char *text,  int x, int y) {
   this->text->write(text, screen, x, y);
}

// Refreshes the screen.
void graphics::update(void) {
   SDL_Flip(screen);
}

graphics *screen = NULL;
