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
/// Mirror
#define NONE 0
#define X    1
#define Y    2
// @}

// @{
/// Type of effects
#define HORIZONTAL        0
#define VERTICAL          1
#define NUMBER_OF_EFFECTS 2
// @}

// @{
/// Sides to face
#define RIGHT 0
#define LEFT  1
// @}

class imageList;
class ttf;

/// Describes screen width, hight and bpp.
///
/// -no detailed description-
struct screenFormat {
   int width;
   int height;
   int bpp;
};

/// Complete screen control.
///
/// This class gives you all the control you need over the screen.
/// The game is played in one screen so there should
/// only be one object of this type.
class graphics {
   private:
      SDL_Surface *screen; // The surface that represents the screen
      imageList *images; // List with all the images used
      ttf *text; // Used to write text into the screen
      screenFormat scrFrmt;

      /// Initializes SDL and SDL_ttf.
      ///
      ///  -no detailed description-
      void init(void);
      /// Creates the surface that will be drawn directly to the screen.
      ///
      /// @param[in] fullscreen Indicates if it's supposed to run on fullscreen.
      /// @param[in] scrFrmt Struct of type screenFormat containing the size and bpp of the window to create.
      void createWindow(const bool fullscreen, const screenFormat scrFrmt);

   public:
      /// Constructor for graphics objects.
      ///
      /// @param[in] fullscreen Indicates if it's supposed to run on fullscreen.
      /// @param[in] scrFrmt Struct of type screenFormat containing the size and bpp of the window to create.
      graphics(const bool fullscreen, screenFormat scrFrmt); // Constructor
      /// Standard Destructor for graphics objects.
      ///
      /// Deletes pointers made for the graphic object and shuts down SDL and SDL_ttf.
      ~graphics(void); // Destructor

      /// Returns the surface of an image.
      ///
      /// Looks for the image in the list of loaded
      /// ones, if it's not there it loads it.
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
      /// @param[in] mirror Indicates if the image is a mirror of the original.
      /// @param[in] angle Number of degrees the image is rotated.
      /// @return Surface of the image.
      SDL_Surface* getImage(const char *imageName, const int alpha = SDL_ALPHA_OPAQUE,
                            const int mirror = NONE, const int angle = 0);

      /// Makes an image face the given side.
      ///
      ///  -no detailed description-
      ///
      /// @param[in] side Side to face.
      /// @param[in] imageSurface Original image.
      /// @return The same image facing the given side.
      SDL_Surface* face(const int side, SDL_Surface *imageSurface);

      /// Loads an image for further use.
      ///
      /// Adds a new image to the list
      ///
      /// @param[in] imageName The image's name, without the "img/" or the ".png".
      /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
      /// @param[in] mirror Indicates if the image is a mirror of the original.
      /// @param[in] angle Number of degrees the image is rotated.
      void newImage(const char *imageName, const int alpha = SDL_ALPHA_OPAQUE,
                    const int mirror = NONE, const int angle = 0);

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

      /// Interface method for the scrFrmt of the graphics object.
      ///
      /// @return The screenFormat struct of the actual graphics object.
      screenFormat getScrFrmt(void);
};

extern graphics *screen;

#endif // GRAPHICS_HPP
