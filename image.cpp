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
#include <string>

#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include "graphics.hpp"
#include "image.hpp"

using namespace std;

// class image

// Loads an image. If there's an error exits.
void image::loadImage(void) {
   SDL_Surface *image;

   // Create a string with the fisical location of the image
   // "img/" + name + ".png"
   string img = "img/";
   string imageName(name);
   string png = ".png";
   string imageDir = img + imageName + png;

   image = IMG_Load( imageDir.c_str() );
   if ( image==NULL ) {
      cout << "\n\t" << SDL_GetError() << "\n\n";
      exit(EXIT_FAILURE);
   } else {
      /// @todo Improve alpha display.
      if (alpha != SDL_ALPHA_OPAQUE) { // Image transparent
         SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
         SDL_SetAlpha(image, SDL_SRCALPHA|SDL_RLEACCEL, alpha);
      }
      this->img = SDL_DisplayFormatAlpha(image);
      if (this->img) SDL_FreeSurface(image);
      else this->img = image;
      // Add the corresponding modifications to the image
      if (angle != 0) this->img = rotozoomSurface(this->img, angle, 1, SMOOTHING_OFF);
      if (mirror == X) this->img = zoomSurface(this->img, -1, 1, SMOOTHING_OFF);
      else if (mirror == Y) this->img = zoomSurface(this->img, 1, -1, SMOOTHING_OFF);
   }
}

// Constructor
image::image(const char *imageName, const int alpha,
             const int mirror, const int angle
            ) {
   name = strdup(imageName);
   this->alpha = alpha;
   this->mirror = mirror;
   this->angle = angle;

   loadImage();
}

// Destructor
image::~image(void) {
   free(name);
   SDL_FreeSurface(img);
}

// Indicates if the given attributes correspond to this image.
bool image::findImage(const char *imageName, const int alpha,
                      const int mirror, const int angle
                     ) {
   return ( !strcmp(imageName, name) &&
            alpha == this->alpha &&
            mirror == this->mirror &&
            angle == this->angle);
}

// ---End---

// class imageList

// Looks for an image in the list.
image* imageList::findImage(const char *imageName, const int alpha,
                            const int mirror, const int angle
                           ) {
   int i=0;
   bool found=false;

   while (i<images.size() && !found) {
      if ( images[i]->findImage(imageName, alpha, mirror, angle) )
         found = true;
      else i++;
   }

   if (!found) return NULL;
   else return images[i];
}

// Looks for an image in the list.
image* imageList::findImage(SDL_Surface *image) {
   int i=0;
   bool found=false;

   while (i<images.size() && !found) {
      if ( images[i]->getSurface() == image )
         found = true;
      else i++;
   }

   if (!found) return NULL;
   else return images[i];
}

// Destructor
imageList::~imageList(void) {
   cout << "Freeing imageList...\t\t";
   for (int i=0; i<images.size(); i++) {
      delete images[i];
   }
   cout << "[ ok ]\n";
}

// Loads the image and then places it at
// the beginning or the list.
void imageList::addImage(const char *imageName, const int alpha,
                         const int mirror, const int angle
                        ) {
   image *temp;

   temp = new image(imageName, alpha, mirror, angle);
   images.push_back(temp);
}

// Returns the surface of an image in the list.
SDL_Surface* imageList::getSurface(const char *imageName, const int alpha,
                                   const int mirror, const int angle
                                  ) {
   image *temp;

   temp = findImage(imageName, alpha, mirror, angle);
   if (temp) return temp->getSurface();
   else return NULL;
}

// Returns an image of the list.
image* imageList::getImage(SDL_Surface *image) {
   return findImage(image);
}

// ---End---
