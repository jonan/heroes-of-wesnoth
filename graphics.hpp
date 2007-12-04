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

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

/*#include <cstdio>
#include <cstdlib>*/

#include "image.hpp"
#include "ttf.hpp"

#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768
#define BPP           16

/// Complete screen control.
///
/// This class gives you all the control you need over the screen.
/// The game is played in one screen so there should
/// only be one object of this type.
class graphics {
   private:
      SDL_Surface *screen; // The surface that represents the screen
      imageList *image; // List with all the images used
      ttf *text; // Used to write text into the screen
      SDL_TimerID timerID; // Unique timer identifier

      /// Initializes SDL, SDL_ttf and SDL_mixer.
      ///
      /// -no detailed description-
      void init(void);
      /// Creates the surface that will be drawn directly to the screen.
      ///
      /// -no detailed description-
      void createWindow(void);

   public:
      graphics(void); // Constructor
      ~graphics(void); // Destructor

      /// Loads an image for further use.
      ///
      /// Adds a new image to the list
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
      void newImage(const char *imageName, const int alpha = SDL_ALPHA_OPAQUE);
      /// Returns the surface of a preveously loaded image.
      ///
      /// -no detailed description-
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      /// @return Surface of the image.
      SDL_Surface* getImage(const char *imageName);

      /// Draws an image previously loaded to the indicated position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      /// @param[in] position Position where the image will be drawn.
      void draw(const char *imageName, SDL_Rect *position);
      /// Draws a surface to the indicated position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] img The images's surface.
      /// @param[in] position Position where the image will be drawn.
      void draw(SDL_Surface *img, SDL_Rect *position);
      /// Writes text in the screen.
      ///
      /// -no detailed description-
      ///
      /// @param[in] text Text to be writen.
      /// @param[in] x The x coordinate of the top left corner of the text.
      /// @param[in] y The y coordinate of the top left corner of the text.
      void write(const char *text,  int x, int y);

      /// Refreshes the screen.
      ///
      /// -no detailed description-
      void update(void);

      /// Executes a function every 50 ms.
      ///
      /// This function is used to refresh the screen every 50 ms.
      ///
      /// The parameter is a little bit special function like this one:
      ///
      /// \code
      /// Uint32 function(Uint32 interval, void *param) {
      ///    //your code
      ///
      ///    return interval;
      /// }
      /// \endcode
      ///
      /// Your code should be the one that has to be execute to refresh the screen.
      void execute(Uint32 (*function)(Uint32, void*));
      /// Ends a execution started with execute(Uint32 (*function)(Uint32, void*)).
      ///
      ///  -no detailed description-
      void endExecution(void);
};

#endif

/* Last Version: Jonan */
