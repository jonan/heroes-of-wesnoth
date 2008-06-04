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

#include <cstdlib>
#include <iostream>

#include "graphics.hpp"
#include "image.hpp"
#include "timer.hpp"
#include "ttf.hpp"

using namespace std;

// Initializes SDL, SDL_ttf and SDL_mixer
void graphics::init(void) {
   cout << "Starting SDL...\t\t\t\t";
   if ( SDL_Init (SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0 ) { // SDL_INIT_AUDIO not yet needed
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   }
   cout << "[ ok ]\n";
   cout << "Starting SDL_ttf...\t\t\t";
   if ( TTF_Init() < 0 ) {
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   }
   cout << "[ ok ]\n";
}

// Creates the surface that will be drawn directly to the screen
void graphics::createWindow(void) {
   /// @todo Add option to change width and height.
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
}

// Destructor
graphics::~graphics(void) {
   cout << "Freeing screen...\n";
   delete image;
   delete text;
   SDL_FreeSurface(screen);
   TTF_Quit();
   SDL_Quit();
}

// Looks for the image in the list of loaded
// ones, if it's not there it loads it.
SDL_Surface* graphics::getImage(const char *imageName) {
   SDL_Surface *temp;

   temp = image->getSurface(imageName);
   if (!temp) { // The image hasn't been loaded.
      newImage(imageName);
      temp = image->getSurface(imageName);
   }

   return temp;
}

// Adds a new image to the list
void graphics::newImage(const char *imageName, const int alpha) {
   image->addImage(imageName, alpha);
}

//Before drawing looks for the image in the list
// of loaded ones, if it's not there it loads it.
void graphics::draw(const char *imageName, SDL_Rect &position) {
   SDL_Surface *temp;

   temp = image->getSurface(imageName);
   if (!temp) { // The image hasn't been loaded.
      newImage(imageName);
      temp = image->getSurface(imageName);
   }

   SDL_BlitSurface(temp, NULL, screen, &position);
}

// Draws a surface to the indicated position.
void graphics::draw(SDL_Surface *img, SDL_Rect &position) {
   SDL_BlitSurface(img, NULL, screen, &position);
}

// Writes text in the screen.
void graphics::write(const char *text,  const int x, const int y) {
   this->text->write(text, screen, x, y);
}


// Puts the screen black.
void graphics::erase(void) {
   SDL_FillRect(screen, NULL, 0);
}
// Refreshes the screen.
void graphics::update(void) {
   SDL_Flip(screen);
}

// Refreshes the screen with an especial effect.
void graphics::transitionEffect(int effect) {
   /// @todo Add/Improve effects.
   timer fps;

   if (effect == -1) effect = rand() % NUMBER_OF_EFFECTS;

   if (effect == HORIZONTAL) {
      for (int x=0; x<SCREEN_WIDTH; x+=5) {
         fps.start();
         SDL_UpdateRect(screen, x, 0, 5, SCREEN_HEIGHT);
         fps.end(10);
      }
   } else if (effect == VERTICAL) {
      for (int y=0; y<SCREEN_HEIGHT; y+=5) {
         fps.start();
         SDL_UpdateRect(screen, 0, y, SCREEN_WIDTH, 5);
         fps.end(10);
      }
   }
}

// Stops the program a number of milisecons.
void graphics::wait(const int ms) {
   SDL_Delay(ms);
}

graphics *screen = NULL;
