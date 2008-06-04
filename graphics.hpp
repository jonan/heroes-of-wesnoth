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
/// The graphic class and global graphics variables.
/// @author Jonan

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL/SDL.h>

#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768
#define BPP           16

// @{
/// Type of effects
#define HORIZONTAL        0
#define VERTICAL          1
#define NUMBER_OF_EFFECTS 2
// @}

class imageList;
class ttf;

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

      // Initializes SDL, SDL_ttf and SDL_mixer.
      void init(void);
      // Creates the surface that will be drawn directly to the screen.
      void createWindow(void);

   public:
      graphics(void); // Constructor
      ~graphics(void); // Destructor

      /// Returns the surface of an image.
      ///
      /// Looks for the image in the list of loaded
      /// ones, if it's not there it loads it.
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      /// @return Surface of the image.
      SDL_Surface* getImage(const char *imageName);

      /// Loads an image for further use.
      ///
      /// Adds a new image to the list
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
      void newImage(const char *imageName, const int alpha = SDL_ALPHA_OPAQUE);

      /// Draws an image to the indicated position.
      ///
      /// Before drawing looks for the image in the list
      /// of loaded ones, if it's not there it loads it.
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      /// @param[in] position Position where the image will be drawn.
      void draw(const char *imageName, SDL_Rect &position);
      /// Draws a surface to the indicated position.
      ///
      /// -no detailed description-
      ///
      /// @param[in] img The images's surface.
      /// @param[in] position Position where the image will be drawn.
      void draw(SDL_Surface *img, SDL_Rect &position);
      /// Writes text in the screen.
      ///
      /// -no detailed description-
      ///
      /// @param[in] text Text to be writen.
      /// @param[in] x The x coordinate of the top left corner of the text.
      /// @param[in] y The y coordinate of the top left corner of the text.
      void write(const char *text,  const int x, const int y);

      /// Puts the screen black.
      ///
      /// -no detailed description-
      void erase(void);
      /// Refreshes the screen.
      ///
      /// -no detailed description-
      void update(void);

      /// Refreshes the screen with an especial effect.
      ///
      /// -no detailed description-
      ///
      /// @param[in] effect Effect to use. If it's -1 the effect is choseen randomly.
      void transitionEffect(int effect = -1);

      /// Stops the program a number of milisecons.
      ///
      /// -no detailed description-
      ///
      /// @param[in] ms Milisecons to wait.
      void wait(const int ms);
};

extern graphics *screen;

#endif // GRAPHICS_HPP
