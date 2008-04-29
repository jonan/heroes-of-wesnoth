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

/// @file
/// The ttf class.
/// @author Jonan

#ifndef TTF_HPP
#define TTF_HPP

#include <SDL/SDL_ttf.h>

/// @todo Add options to change color, size, etc.

/// Represents text on the screen.
///
/// This class is only meant to be used by graphics, which
/// controls every single thing represented on the screen.
class ttf{
   private:
      TTF_Font *font;
      SDL_Surface *textSurface;
      SDL_Rect position;
      SDL_Color color;

   public:
      ttf(void); // Constructor
      ~ttf(void); // Destrucor

      /// Writes a text into a surface.
      ///
      /// -no detailed description-
      ///
      /// @param[in] text A string with the text to write.
      /// @param[in] surface The surface where to draw the text.
      /// @param[in] x The x coordinate of the top left corner of the text.
      /// @param[in] y The y coordinate of the top left corner of the text.
      void write(const char *text, SDL_Surface *surface, const int x, const int y);
};

#endif // TTF_HPP
