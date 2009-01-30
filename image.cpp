/*
This file is part of Heroes of Wesnoth.
Copyright (C) 2007, 2008, 2009 Jon Ander Peñalba <jonan88@gmail.com>

Heroes of Wesnoth is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

Heroes of Wesnoth is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include "image.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

// std
using std::cout;
using std::string;
// video_engine
using video_engine::Graphics;

// class image

// Constructor
Graphics::Image::Image(const char *image_name, const int alpha,
                       const int mirror, const int angle
                      ) {
  name = strdup(image_name);
  this->alpha = alpha;
  this->mirror = mirror;
  this->angle = angle;

  loadImage();
}

// Destructor
Graphics::Image::~Image(void) {
  free(name);
  SDL_FreeSurface(img);
}

// Indicates if the given attributes correspond to this image.
bool Graphics::Image::findImage(const char *image_name, const int alpha,
                                const int mirror, const int angle
                               ) {
  return ( !strcmp(image_name, name) &&
           alpha == this->alpha &&
           mirror == this->mirror &&
           angle == this->angle );
}

// Loads an image. If there's an error exits.
void Graphics::Image::loadImage(void) {
  SDL_Surface *image;

  // Create a string with the fisical location of the image
  // "img/" + name + ".png"
  string img = "img/";
  string image_name(name);
  string png = ".png";
  string image_dir = img + image_name + png;

  image = IMG_Load( image_dir.c_str() );
  if ( image==NULL ) {
    cout << "\n\t" << SDL_GetError() << "\n\n";
    exit(EXIT_FAILURE);
  } else {
    /// @todo Improve alpha display.
    if (alpha != OPAQUE) { // Image transparent
      SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
      SDL_SetAlpha(image, SDL_SRCALPHA|SDL_RLEACCEL, alpha);
    }
    this->img = SDL_DisplayFormatAlpha(image);
    if (this->img)
      SDL_FreeSurface(image);
    else
      this->img = image;
    // Add the corresponding modifications to the image
    if (angle != 0) this->img = rotozoomSurface(this->img, angle, 1, SMOOTHING_OFF);
    if (mirror == X)
      this->img = zoomSurface(this->img, -1, 1, SMOOTHING_OFF);
    else if (mirror == Y)
      this->img = zoomSurface(this->img, 1, -1, SMOOTHING_OFF);
  }
}

// ---End---

// class imageList

// Destructor
Graphics::ImageList::~ImageList(void) {
  cout << "Freeing imageList...\t\t";
  for (unsigned int i=0; i<images.size(); i++) {
    delete images[i];
  }
  cout << "[ ok ]\n";
}

// Loads the image and then places it at
// the beginning or the list.
void Graphics::ImageList::addImage(const char *image_name, const int alpha,
                                   const int mirror, const int angle
                                  ) {
  Image *temp;

  temp = new Image(image_name, alpha, mirror, angle);
  images.push_back(temp);
}

// Returns the surface of an image in the list.
SDL_Surface* Graphics::ImageList::getSurface(const char *image_name, const int alpha,
                                             const int mirror, const int angle
                                            ) {
  Image *temp;

  temp = findImage(image_name, alpha, mirror, angle);
  if (temp)
    return temp->getSurface();
  else
    return NULL;
}

// Returns an image of the list.
Graphics::Image* Graphics::ImageList::getImage(SDL_Surface *image) {
  return findImage(image);
}

// Looks for an image in the list.
Graphics::Image* Graphics::ImageList::findImage(const char *image_name, const int alpha,
                                                const int mirror, const int angle
                                               ) {
  unsigned int i=0;
  bool found=false;

  while (i<images.size() && !found) {
    if ( images[i]->findImage(image_name, alpha, mirror, angle) )
      found = true;
    else
      i++;
  }

  if (!found)
    return NULL;
  else
    return images[i];
}

// Looks for an image in the list.
Graphics::Image* Graphics::ImageList::findImage(SDL_Surface *image) {
  unsigned int i=0;
  bool found=false;

  while (i<images.size() && !found) {
    if ( images[i]->getSurface() == image )
      found = true;
    else i++;
  }

  if (!found)
    return NULL;
  else
    return images[i];
}

// ---End---
