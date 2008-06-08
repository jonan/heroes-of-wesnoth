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

#include <iostream>

#include "ttf.hpp"

using namespace std;

// Constructor
ttf::ttf(void) {
   font = TTF_OpenFont("font/DejaVuSans.ttf", 14);
   if (font == NULL) {
      cout << "\n\t" << SDL_GetError() << "\n\n";
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
ttf::~ttf(void) {
   TTF_CloseFont(font);
}

// Writes a text into a surface.
void ttf::write(const char *text, SDL_Surface *surface, const int x, const int y) {
   textSurface = TTF_RenderText_Solid(font, text, color);

   position.x = x;
   position.y = y;
   position.w = textSurface->w;
   position.h = textSurface->h;

   SDL_BlitSurface(textSurface, NULL, surface, &position);
   // After being used, free the surface
   SDL_FreeSurface(textSurface);
}
