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
along with Heroes of Wesnoth. If not, see <http://www.gnu.org/licenses/>
*/

#include "boot.hpp"

#include <ctime>

#include "tinyxml/tinyxml.h"

#include "events.hpp"
#include "graphics.hpp"
#include "xml_manager.hpp"

// events_engine
using events_engine::input;
// video_engine
using video_engine::screen;

// Loads the engine's global objects.
void startEngine(const bool fullscreen, const int width, const int height) {
  screen = video_engine::Graphics::getInstance();
  screen->createWindow(fullscreen, width, height);
  input = events_engine::Events::getInstance();
}

// Loads the images that will be used almost every
// time the game is executed.
void loadMainImages(void) {
  screen->newImage("alpha", 50);
  screen->newImage("button");
  screen->newImage("button-active");
  screen->newImage("button-pressed");
  screen->newImage("heroes-logo");
  screen->newImage("wesnoth");
  screen->newImage("cursors/normal");
  screen->newImage("cursors/attack");
  screen->newImage("cursors/move");
  screen->newImage("cursors/select-illegal");
  screen->newImage("cursors/wait");
}

// Loads the XML configuration files.
void loadXmlFiles(void) {
  XmlManager* xml = XmlManager::getInstance();

  // Load the XML files that need IDs
  const char* files_with_id[] = { HEROES_XML_FILE,
                                  ITEMS_XML_FILE,
                                  TERRAIN_XML_FILE,
                                  UNITS_XML_FILE    };
  int size = sizeof(files_with_id)/sizeof(files_with_id[0]);

  TiXmlDocument *file;
  for (int i=0; i<size; i++) {
    file = xml->loadFile(files_with_id[i]);
    xml->setIds(file);
  }

  // Load the rest of XML files
  const char* other_files[] = { SMOOTH_IMAGES_XML_FILE,
                                SMOOTH_RULES_XML_FILE   };
  size = sizeof(other_files)/sizeof(other_files[0]);

  for (int j=0; j<size; j++)
    xml->loadFile(other_files[j]);
}

// Starts the engine and loads the main images.
void boot(const bool fullscreen, const int width, const int height) {
  srand( time(NULL) ); // Set seed for random numbers
  startEngine(fullscreen, width, height);
  loadMainImages();
  loadXmlFiles();
}

// Exits the game.
void quit(void) {
  exit(EXIT_SUCCESS);
}
