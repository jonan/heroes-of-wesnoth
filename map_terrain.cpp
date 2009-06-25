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

#include "map.hpp"

#include <cstdlib>
#include <deque>
#include <iostream>

#include "tinyxml/tinyxml.h"

#include "cell.hpp"
#include "graphics.hpp"
#include "xml_manager.hpp"

using video_engine::screen;

// If cell is NULL, applies the terrain to all the cells in the map.
void Map::setTerrain(const char *id, Cell *cell) {
  TiXmlDocument *document = XmlManager::getInstance()->getFile(TERRAIN_XML_FILE);
  TiXmlElement *root = document->RootElement();

  TiXmlElement *temp = root->FirstChildElement();
  if (strlen(id) > 2) {
    while( strcmp(temp->Attribute("name"), id) )
      temp = temp->NextSiblingElement();
    id = temp->Attribute("id");
  } else {
    while ( strcmp(temp->Attribute("id"), id) )
      temp = temp->NextSiblingElement();
  }

  // Set base terrain
  bool special_image = false;
  if (temp->FirstChild("base")) {
    setTerrain(temp->FirstChildElement("base")->GetText(), cell);
    special_image = true;
  }

  // Set alpha (for all cells)
  SDL_Surface *alpha = screen->getImage("alpha", 50);
  // Set stars (for all cells)
  std::deque<SDL_Surface*> stars_images;
  stars_images.push_back( screen->getImage("terrain/stars/blue1") );
  stars_images.push_back( screen->getImage("terrain/stars/blue2") );
  stars_images.push_back( screen->getImage("terrain/stars/blue3") );
  stars_images.push_back( screen->getImage("terrain/stars/blue4") );
  stars_images.push_back( screen->getImage("terrain/stars/blue5") );
  stars_images.push_back( screen->getImage("terrain/stars/blue6") );
  stars_images.push_back( screen->getImage("terrain/stars/blue7") );
  // Set the terrain
  std::deque<SDL_Surface*> terrain_images;
  TiXmlElement *temp_img;
  for (temp_img = temp->FirstChildElement("image"); temp_img; temp_img = temp_img->NextSiblingElement())
    terrain_images.push_back( screen->getImage(temp_img->GetText()) );
  bool passable = strcmp(temp->Attribute("passable"), "false");

  int random_number;
  if (!cell) { // Set the attributes to all the cells.
    for (int i=0; i<map_width; i++)
      for (int j=0; j<map_height; j++) {
        map[i][j].setAlpha(*alpha);
        random_number = rand() % stars_images.size();
        map[i][j].setStars(*stars_images[random_number]);
        random_number = rand() % terrain_images.size();
        if (!special_image)
          map[i][j].addImage(*terrain_images[random_number], id);
        else
          map[i][j].addSpecialImage(*terrain_images[random_number]);
        // If the cell is in one of the maps borders, block movement
        if ( i==0 || i==map_width-1 || j==0 || j==map_height-1)
          map[i][j].setPassable(false);
        else
          map[i][j].setPassable(passable);
      }
  } else { // Set the attributes to a given cell.
    cell->setAlpha(*alpha);
    random_number = rand() % stars_images.size();
    cell->setStars(*stars_images[random_number]);
    random_number = rand() % terrain_images.size();
    if (!special_image)
      cell->addImage(*terrain_images[random_number], id);
    else
      cell->addSpecialImage(*terrain_images[random_number]);
    // If the cell is in one of the maps borders, block movement
    int x, y;
    cell->getCoordinates(x, y);
    if ( x==0 || x==map_width-1 || y==0 || y==map_height-1)
      cell->setPassable(false);
    else
      cell->setPassable(passable);
  }
}
