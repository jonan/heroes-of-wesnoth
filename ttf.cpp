/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007-2008 Jon Ander Peñalba <jonan88@gmail.com>

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

#include "ttf.hpp"

#include <cstdlib>
#include <iostream>

// video_engine
using video_engine::Graphics;

// Constructor
Graphics::Ttf::Ttf(void) {
  font = TTF_OpenFont("font/DejaVuSans.ttf", 14);
  if (font == NULL) {
    std::cout << "\n\t" << SDL_GetError() << "\n\n";
    exit(EXIT_FAILURE);
  }

  // Initialize position
  position.x = 0;
  position.y = 0;
  position.w = 0;
  position.h = 0;

  color.r = color.g = color.b = 255; // Put color to white
}

// Destructor
Graphics::Ttf::~Ttf(void) {
  TTF_CloseFont(font);
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

// The text is centered in between the given positions.
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
