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

#include "ttf.hpp"

#include <cstdlib>
#include <iostream>

#include <SDL/SDL_ttf.h>

// std
using std::cout;
// video_engine
using video_engine::Graphics;

// Constructor
Graphics::Ttf::Ttf(void) {
  cout << "Starting SDL_ttf...\t\t";
  if ( TTF_Init() < 0 ) {
    cout << "[fail]\n\n" << SDL_GetError() << "\n\n";
    exit(EXIT_FAILURE);
  }
  cout << "[ ok ]\n";

  font = TTF_OpenFont("font/DejaVuSans.ttf", 14);
  if (font == NULL) {
    cout << "\n\t" << SDL_GetError() << "\n\n";
    exit(EXIT_FAILURE);
  }

  color.r = color.g = color.b = 255; // Set color to white
}

// Destructor
Graphics::Ttf::~Ttf(void) {
  TTF_CloseFont(font);
  TTF_Quit();
}

// Writes a text into a surface.
void Graphics::Ttf::write(const char *text, SDL_Surface *surface, const int x, const int y) {
  text_surface = TTF_RenderUTF8_Blended(font, text, color);

  position.x = x;
  position.y = y;
  position.w = text_surface->w;
  position.h = text_surface->h;

  SDL_BlitSurface(text_surface, NULL, surface, &position);
  // After being used, free the surface
  SDL_FreeSurface(text_surface);
}

// Writes a text centered in a surface.
void Graphics::Ttf::writeCentered(const char *text, SDL_Surface *surface,
                                  const int left_x, const int right_x,
                                  const int top_y, const int bottom_y
                                 ) {
  text_surface = TTF_RenderUTF8_Blended(font, text, color);

  position.x = ((right_x-left_x-text_surface->w)/2)+left_x;
  position.y = ((bottom_y-top_y-text_surface->h)/2)+top_y;
  position.w = text_surface->w;
  position.h = text_surface->h;

  SDL_BlitSurface(text_surface, NULL, surface, &position);
  // After being used, free the surface
  SDL_FreeSurface(text_surface);
}
