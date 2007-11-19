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

#include "graphics.hpp"

// Initializes SDL, SDL_ttf and SDL_mixer
void graphics::init(void) {
   printf("Starting SDL...\t\t\t\t");
   if ( SDL_Init (SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0 ) { // SDL_INIT_AUDIO not yet needed
      printf("[fail]\n\n%s\n\n", SDL_GetError ());
      exit(EXIT_FAILURE);
   }
   atexit(SDL_Quit);
   printf("[ ok ]\n");
   printf("Starting SDL_ttf...\t\t\t");
   if ( TTF_Init() < 0 ) {
      printf("[fail]\n\n%s\n\n", SDL_GetError ());
      exit(EXIT_FAILURE);
   }
   atexit(TTF_Quit);
   printf("[ ok ]\n");
   printf("Starting SDL_mixer...\t\t\t");
   if ( Mix_OpenAudio(22050, AUDIO_S16, 2, 4096) ) {
      printf("[fail]\n\n%s\n\n", SDL_GetError ());
      exit(EXIT_FAILURE);
   }
   atexit(Mix_CloseAudio);
   printf("[ ok ]\n");
}

// Creates the surface that will be drawn directly to the screen
void graphics::createWindow(void) {
   printf("Opening %ix%i window...\t\t", SCREEN_WIDTH, SCREEN_HEIGHT);
   SDL_WM_SetCaption ("Heroes of Wesnoth", NULL);
   // Not using fullscreen to prevent reseting computer after program crash.
   // This will change in final version.
   screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, BPP, SDL_DOUBLEBUF | SDL_ANYFORMAT);// | SDL_FULLSCREEN);
   if (screen == NULL) {
      printf ("[fail]\n\n%s\n\n", SDL_GetError ());
      exit(EXIT_FAILURE);
   }
   printf("[ ok ]\n");
}

// Constructor
graphics::graphics(void) {
   init();
   createWindow();
   image = new imageList;
   text = new ttf(screen);
   timerID = 0;
}

// Destructor
graphics::~graphics(void) {
   printf("Freeing screen...\n");
   SDL_FreeSurface(screen);
   delete image;
   delete text;
   if (timerID !=0) SDL_RemoveTimer(timerID);
}

// Adds a new image to the list
void graphics::newImage(const char *imageName, const int alpha) {
   image->addImage(imageName, alpha);
}

// Returns the surface of a preveously loaded image.
SDL_Surface* graphics::getImage(const char imageName[20]) {
   SDL_Surface *temp;

   temp = image->findImage(imageName)->img;
   return temp;
}

/// @todo Check this
/*

Don't know why doesn't this work... I'll check back sortly

SDL_Surface* graphics::getImage(char imageName[20]) {
   image *temp;

   temp = image->findImage(imageName);
   return temp->img;
}
*/

// Draws an image previously loaded to the indicated position.
void graphics::draw(const char imageName[20], SDL_Rect *position) {
   SDL_Surface *temp;

   temp = image->findImage(imageName)->img;
   SDL_BlitSurface(temp, NULL, screen, position);
}

// Draws a surface to the indicated position.
void graphics::draw(SDL_Surface *img, SDL_Rect *position) {
   SDL_BlitSurface(img, NULL, screen, position);
}

// Writes text in the screen.
void graphics::write(const char *text,  int x, int y) {
   this->text->write(text,  x, y);
}

// Refreshes the screen.
void graphics::update(void) {
   SDL_Flip(screen);
}

// This function is used to refresh the screen every 50 ms.
void graphics::execute(Uint32 (*function)(Uint32, void*)) {
   if (timerID == 0) {
      printf("Creating new timer...\n");
      timerID = SDL_AddTimer(10, function, NULL);
   } else {
      printf("Deleting timer...\n");
      SDL_RemoveTimer(timerID);
      printf("Creating new timer...\n");
      timerID = SDL_AddTimer(10, function, NULL);
   }
}

// Ends a execution started with execute(Uint32 (*function)(Uint32, void*)).
void graphics::endExecution(void) {
   SDL_RemoveTimer(timerID);
   timerID=0;
}

/* Last Version: Jonan */
