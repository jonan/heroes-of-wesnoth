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

#include "image.hpp"

// class image

// Returns a pointer to the image that needs to be
// load if there's no error. Otherwise, exits the program.
SDL_Surface* image::loadImage(const char *imageName, const int alpha) {
   SDL_Surface *image;
   std::string *imageDir;

   imageDir = new std::string(imageName);
   // Create a string with the fisical location of the image
   //  "img/" + imageName + ".png"
   imageDir->insert(0, "img/");
   imageDir->insert( strlen(imageName)+4 , ".png");

   printf("Loading \"%s\"...\t\t", imageName);
   // If the image name is to sort leave more space
   if ( strlen(imageName)<11 ) printf("\t");
   image = IMG_Load( imageDir->c_str() );
   if ( image==NULL ) {
      printf("[fail]\n\n%s\n\n", SDL_GetError ());
      exit(EXIT_FAILURE);
   } else {
      /// @todo Improve alpha display.
      //SDL_SetAlpha(image, SDL_SRCALPHA|SDL_RLEACCEL, alpha);
      if (alpha != 255) { // Image transparent
         SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
         SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
      }
      image = SDL_DisplayFormatAlpha(image);
      printf("[ ok ]\n");
      return image;
   }
   delete imageDir;
}

// Constructor
image::image(const char *imageName, const int alpha, image *next) {
   name = new char [strlen(imageName)];

   strcpy(name, imageName);
   this->next=next;
   img = this->loadImage(name, alpha);
}

// Destructor
image::~image(void) {
   printf("Freeing \"%s\"...\n", name);
   delete name;
   SDL_FreeSurface(img);
}

// Returns the image name.
char* image::getName(void) {
   return name;
}

// Returns the next image in the imageList.
image* image::getNext(void) {
   return next;
}

/// @todo get getSurface() working.
/* Don't know why it doesn't work

SDL_Surface* getSurface(void) {
   return img;
}

*/

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
         printf("\nSearch for file \"%s\" failed.\n\n", imageName);
         exit(EXIT_FAILURE);
         }
   else return temp;
}

// ---End---

/* Last Version: Jonan */
