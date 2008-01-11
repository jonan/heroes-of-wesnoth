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

#include <SDL/SDL_image.h>

#include <string>

#include "image.hpp"

// class image

// Loads an image with the alpha value indicated,
// if ther's an error, exits the program.
void image::loadImage(const int alpha) {
   SDL_Surface *image = NULL;

   // Create a string with the fisical location of the image
   // "img/" + name + ".png"
   std::string img = "img/";
   std::string imageName(name);
   std::string png = ".png";
   std::string imageDir = img + imageName + png;

   printf("Loading \"%s\"...\t\t", name);
   // If the image name is to sort leave more space
   if ( strlen(name)<11 ) printf("\t");
   image = IMG_Load( imageDir.c_str() );
   if ( image==NULL ) {
      printf("[fail]\n\n%s\n\n", SDL_GetError ());
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
      printf("[ ok ]\n");
   }
}

// Constructor
image::image(const char *imageName, const int alpha, image *next) {
   name = strdup(imageName);
   this->next=next;
   loadImage(alpha);
}

// Destructor
image::~image(void) {
   printf("Freeing \"%s\"...\t\t", name);
   // If the image name is to sort leave more space
   if ( strlen(name)<11 ) printf("\t");
   delete [] name;
   SDL_FreeSurface(img);
   printf("[ ok ]\n");
}

// Returns the image name.
char* image::getName(void) {
   return name;
}

// Returns the next image in the imageList.
image* image::getNext(void) {
   return next;
}

SDL_Surface* image::getSurface(void) {
   return img;
}

// ---End---

// class imageList

// Constructor
imageList::imageList(void) : first(NULL) {}

// Destructor
imageList::~imageList(void) {
   /// @todo Check if everything is deleted.
   image *temp, *next;

   printf("Deleting imageList...\n");
   temp=first;
   next=temp->getNext();
   while (next!=NULL) {
      delete temp;
      temp=next;
      next=temp->getNext();
   }
   delete temp;
}

// Loads the image and then places it at
// the beginning or the list.
void imageList::addImage(const char *imageName, const int alpha) {
   image *temp;

   temp = new image(imageName, alpha, first);
   first = temp;
}

// If the image doesn't exist, exits the program and
// prints an error message.
image* imageList::findImage(const char *imageName) {
   image *temp;

   temp = first;
   if (temp!=NULL)
      // Go through all the list until the image is found
      while ( strcmp(temp->getName(), imageName) != 0 )
         temp = temp->getNext();
   if (temp==NULL) {
         printf("\nSearch for file \"%s\" failed.\n\n", *imageName);
         exit(EXIT_FAILURE);
         }
   else return temp;
}

// Returns the surface of an image in the list.
SDL_Surface* imageList::getSurface(const char *imageName) {
   return findImage(imageName)->getSurface();
}

// ---End---

/* Last Version: Jonan */
