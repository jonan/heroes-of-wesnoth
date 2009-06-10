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
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include "graphics.hpp"

#include <cstdlib>
#include <iostream>

#include "events.hpp"
#include "image.hpp"
#include "timer.hpp"
#include "ttf.hpp"

// std
using std::cout;
// events_engine
using events_engine::input;

namespace video_engine {

// Singleton pattern constructor
Graphics* Graphics::getInstance(void) {
  static Graphics instance;
  return &instance;
}

// Destructor
Graphics::~Graphics(void) {
  delete images;
  delete text;
  SDL_Quit();
}

// Creates the surface that will be drawn directly to the screen
void Graphics::createWindow(const bool fullscreen, int width, int height) {
  if (!screen) {
    SDL_flags = (SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_VIDEORESIZE);
    if (fullscreen) SDL_flags |= SDL_FULLSCREEN;

    bpp = SDL_VideoModeOK( width, height, 16, SDL_flags);
    if (!bpp) {
      cout << "The choosen resolution (" << width << "x" << height 
	   << ") is not valid on your system. Trying default (1024x768%16)...\n";
      width = 1024;
      height = 768;
      bpp = 16;
    }

    cout << "Opening " << width << "x" << height << "%" << bpp << " window...\t";
    this->width = width;
    this->height = height;

    // Set the video mode
    screen = SDL_SetVideoMode(width, height, bpp, SDL_flags);
    SDL_WM_SetCaption("Heroes of Wesnoth", NULL);

    if (screen == NULL) {
      cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
    }
    cout << "[ ok ]\n";
  }
}

// Adds a new image to the list
void Graphics::newImage(const char *image_name, const int alpha,
                        const int mirror, const int angle
                       ) {
  images->addImage(image_name, alpha, mirror, angle);
}

// Looks for the image in the list of loaded
// ones, if it's not there it loads it.
SDL_Surface* Graphics::getImage(const char *image_name, const int alpha,
                                const int mirror, const int angle
                               ) {
  SDL_Surface *temp;

  temp = images->getSurface(image_name, alpha, mirror, angle);
  if (!temp) { // The image hasn't been loaded.
    newImage(image_name, alpha, mirror, angle);
    temp = images->getSurface(image_name, alpha, mirror, angle);
  }

  return temp;
}

// Makes an image face the given side.
SDL_Surface* Graphics::face(const int side, SDL_Surface *image_surface) {
  Image* temp;

  temp = images->getImage(image_surface);
  if (temp->getMirror() == X) {
    if (side == RIGHT)
      return getImage(temp->getName(), temp->getAlphaValue(),
                      NONE, temp->getAngle());
    else
      return image_surface;
  } else {
    if (side == RIGHT)
      return image_surface;
    else
      return getImage(temp->getName(), temp->getAlphaValue(),
                      X, temp->getAngle());
  }
}

// This function should only be called inside the
// Events class after a SDL_VIDEORESIZE event.
void Graphics::resize(const int width, const int height) {
  this->width = width;
  this->height = height;
  screen = SDL_SetVideoMode(width, height, bpp, SDL_flags);
}

// Returns the actual screen's size.
void Graphics::getScreenSize(int &width, int &height) {
  width = this->width;
  height = this->height;
}

// Before drawing looks for the image in the list
// of loaded ones, if it's not there it loads it.
void Graphics::draw(const char *image_name, SDL_Rect &position) {
  SDL_Surface *temp;

  temp = getImage(image_name);

  SDL_BlitSurface(temp, NULL, screen, &position);
}

// Draws a surface to the indicated position.
void Graphics::draw(SDL_Surface *img, SDL_Rect &position) {
  SDL_BlitSurface(img, NULL, screen, &position);
}

// Writes text in the screen.
void Graphics::write(const char *text,  const int x, const int y) {
  this->text->write(text, screen, x, y);
}

// The text is centered in between the given positions.
void Graphics::writeCentered(const char *text,
                             const int left_x, const int right_x,
                             const int top_y, const int bottom_y) {
  this->text->writeCentered(text, screen, right_x, left_x, top_y, bottom_y);
}

// Puts the screen black.
void Graphics::erase(void) {
  SDL_FillRect(screen, NULL, 0);
}

// Refreshes the screen.
void Graphics::update(void) {
  input->drawMouse();
  SDL_Flip(screen);
}

// Refreshes the screen with an especial effect.
void Graphics::transitionEffect(int effect) {
  /// @todo Add/Improve effects.
  Timer fps;

  if (effect == RANDOM)
    effect = rand() % NUMBER_OF_EFFECTS;

  switch (effect) {
    case HORIZONTAL:
      for (int x=0; x<width; x+=5) {
        fps.start();
        SDL_UpdateRect(screen, x, 0, 5, height);
        fps.end(10);
      }
      break;
    case VERTICAL:
      for (int y=0; y<height; y+=5) {
        fps.start();
        SDL_UpdateRect(screen, 0, y, width, 5);
        fps.end(10);
      }
      break;
    default: {} // Imposible case
  }
}

// Constructor
Graphics::Graphics(void) {
  screen = NULL;
  init();
  images = new ImageList;
  text = new Ttf;
}

// Initializes SDL and SDL_ttf.
void Graphics::init(void) {
  cout << "Starting SDL...\t\t\t";
  if ( SDL_Init (SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0 ) { // SDL_INIT_AUDIO not yet needed
    cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
    exit(EXIT_FAILURE);
  }
  cout << "[ ok ]\n";
}

Graphics *screen = NULL;

} // namespace video_engine
