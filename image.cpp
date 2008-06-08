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

#include "image.hpp"

using namespace std;

// class image

// Loads an image with the alpha value indicated,
// if ther's an error, exits the program.
void image::loadImage(const int alpha) {
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
   }
}

// Constructor
image::image(const char *imageName, const int alpha) {
   name = strdup(imageName);
   loadImage(alpha);
}

// Destructor
image::~image(void) {
   free(name);
   SDL_FreeSurface(img);
}

// Returns the image name.
char* image::getName(void) {
   return name;
}

SDL_Surface* image::getSurface(void) {
   return img;
}

// ---End---

// class imageList

// Looks for an image in the list. If the
// image doesn't exist, exits the program
image* imageList::findImage(const char *imageName) {
   int i=0;
   bool found=false;

   while (i<images.size() && !found) {
      if ( strcmp(images[i]->getName(), imageName) == 0 )
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
void imageList::addImage(const char *imageName, const int alpha) {
   image *temp;

   temp = new image(imageName, alpha);
   images.push_back(temp);
}

// Returns the surface of an image in the list.
SDL_Surface* imageList::getSurface(const char *imageName) {
   image *temp;

   temp = findImage(imageName);
   if (temp) return temp->getSurface();
   else return NULL;
}

// ---End---
