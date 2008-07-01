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
   cout << "Starting SDL...\t\t\t";
   if ( SDL_Init (SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0 ) { // SDL_INIT_AUDIO not yet needed
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   }
   cout << "[ ok ]\n";
   cout << "Starting SDL_ttf...\t\t";
   if ( TTF_Init() < 0 ) {
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   }
   cout << "[ ok ]\n";
}

// Creates the surface that will be drawn directly to the screen
void graphics::createWindow(const bool fullscreen, const int width, const int height, const int bpp) {
   cout << "Opening " << width << "x" << height << "%" << bpp << " window...\t";
   this->width = width;
   this->height = height;

   SDL_WM_SetCaption ("Heroes of Wesnoth", NULL);
   /// @todo put SDL standard video flags into a var. No need to write them so often.
   if (fullscreen) {
      screen = SDL_SetVideoMode (width, height, bpp, SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_FULLSCREEN);
   } else {
      screen = SDL_SetVideoMode (width, height, bpp, SDL_DOUBLEBUF | SDL_ANYFORMAT);
   }

   if (screen == NULL) {
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   }
   cout << "[ ok ]\n";
}

// Constructor
graphics::graphics(const bool fullscreen, int width, int height) {
   init();

   // Validate the resolution input by user.
   // Only check with SDL_FULLSCREEN is neccessary and useful.
   // Without SDL_FULLSCREEN _all_ screen formats would be valid.
   int bpp = SDL_VideoModeOK( width, height, 16, SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_FULLSCREEN );
   if (!bpp) {
      cout << "The choosen resolution (" << width << "x" << height 
           << ") is not valid on your system. Trying default (1024x768)...\n";
      width = 1024;
      height = 768;
      bpp = 16;
   }
   createWindow(fullscreen, width, height, bpp);

   images = new imageList;
   text = new ttf;
}

// Destructor
graphics::~graphics(void) {
   delete images;
   delete text;
   SDL_FreeSurface(screen);
   TTF_Quit();
   SDL_Quit();
}

// Looks for the image in the list of loaded
// ones, if it's not there it loads it.
SDL_Surface* graphics::getImage(const char *imageName, const int alpha,
                                const int mirror, const int angle
                               ) {
   SDL_Surface *temp;

   temp = images->getSurface(imageName, alpha, mirror, angle);
   if (!temp) { // The image hasn't been loaded.
      newImage(imageName, alpha, mirror, angle);
      temp = images->getSurface(imageName, alpha, mirror, angle);
   }

   return temp;
}

// Returns the actual screen's size.
void graphics::getScreenSize(int &width, int &height) {
   width = this->width;
   height = this->height;
}

// Makes an image face the given side.
SDL_Surface* graphics::face(const int side, SDL_Surface *imageSurface) {
   /// @todo merge this function with faceRight()
   image* temp;

   temp = images->getImage(imageSurface);
   if (temp->getMirror() == X) {
      if (side == RIGHT)
         return getImage(temp->getName(), temp->getAlpha(),
                         NONE, temp->getAngle());
      else return imageSurface;
   } else {
      if (side == RIGHT) return imageSurface;
      else return getImage(temp->getName(), temp->getAlpha(),
                           X, temp->getAngle());
   }
}

// Adds a new image to the list
void graphics::newImage(const char *imageName, const int alpha,
                        const int mirror, const int angle
                       ) {
   images->addImage(imageName, alpha, mirror, angle);
}

// Before drawing looks for the image in the list
// of loaded ones, if it's not there it loads it.
void graphics::draw(const char *imageName, SDL_Rect &position) {
   SDL_Surface *temp;

   temp = getImage(imageName);

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
