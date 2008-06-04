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
/// The image and imageList classes.
/// @author Jonan

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <deque>

#include <SDL/SDL.h>

using namespace std;

/// A class to control images.
///
/// It should only be used by the imageList class.
class image {
   private:
      char *name; // Unique name of each image (the fisical image name)
      SDL_Surface *img; // Image's surface

      // Loads an image with the alpha value indicated,
      // if ther's an error, exits the program.
      void loadImage(const int alpha);

   public:
      /// @param[in] imageName The image's name, without the "img/" or the ".png"
      /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque)
      image(const char *imageName, const int alpha); // Constructor
      ~image(void); // Destructor

      /// Returns the image name.
      ///
      /// -no detailed description-
      ///
      /// @return image name.
      char* getName(void);
      /// Returns the image's surface.
      ///
      /// -no detailed description-
      ///
      /// @return image's surface.
      SDL_Surface* getSurface(void);
};

/// A list of image classes.
///
/// Store an image and look for any other previously
/// stored. It should only be used by graphics.
class imageList {
   private:
      deque<image*> images;

      // Looks for an image in the list. If the
      // image doesn't exist, exits the program
      image* findImage(const char *imageName);

   public:
      ~imageList(void); // Destructor

      /// Adds the image to the list.
      ///
      /// Loads the image and then places it at
      /// the beginning or the list.
      ///
      /// @param[in] imageName  The image's name, without the "img/" or the ".png".
      /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
      void addImage(const char *imageName, const int alpha);
      /// Returns the surface of an image in the list.
      ///
      /// -no detailed description-
      ///
      /// @param[in] imageName  The image's name, without the "img/" or the ".png".
      /// @return Surface of an image in the list.
      SDL_Surface* getSurface(const char *imageName);
};

#endif // IMAGE_HPP
