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
#include <iostream>

#include "tinyxml/tinyxml.h"

#include "cell.hpp"
#include "graphics.hpp"
#include "xml_manager.hpp"

using video_engine::screen;

// Puts an item on a cell.
void Map::setItem(const char *id, Cell &position) {
  TiXmlDocument *document = XmlManager::getInstance()->getFile(ITEMS_XML_FILE);
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

  std::deque<SDL_Surface*> item_images;
  TiXmlElement *temp_img;
  for (temp_img = temp->FirstChildElement("image"); temp_img; temp_img = temp_img->NextSiblingElement())
    item_images.push_back( screen->getImage(temp_img->GetText()) );

  position.setItemType(id);
  int random_number;
  random_number = rand() % item_images.size();
  position.addSpecialImage(*item_images[random_number]);
}
