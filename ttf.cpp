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

#include "ttf.hpp"

// Constructor
ttf::ttf(SDL_Surface *screen) {
   this->screen = screen;

   printf("Loading font...\t\t\t\t");
   font = TTF_OpenFont("font/DejaVuSans.ttf", 14);
   if (font == NULL) {
      printf("[fail]\n\n%s\n\n", SDL_GetError ());
      exit(1);
   } else
      printf("[ ok ]\n");

   // Initialize position
   position.x = 0;
   position.y = 0;
   position.w = 0;
   position.h = 0;

   color.r = color.g = color.b = 255; // Put color to white
}

// Destructor
ttf::~ttf(void) {
   printf("Freeing font...\n");
   TTF_CloseFont(font);
}

// Writes a text into the screen
void ttf::write(const char *text,  const int x, const int y) {
   textSurface = TTF_RenderText_Solid(font, text, color);

   position.x = x;
   position.y = y;
   position.w = textSurface->w;
   position.h = textSurface->h;

   SDL_BlitSurface(textSurface, NULL, screen, &position);
   // After being used, free the surface
   SDL_FreeSurface(textSurface);
}

/* Last Version: Jonan */
