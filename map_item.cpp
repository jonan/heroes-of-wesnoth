/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007-2008 Jon Ander Peñalba <jonan88@gmail.com>

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

#include "map.hpp"

#include <cstdlib>
#include <iostream>

#include "cell.hpp"
#include "graphics.hpp"

// video_engine
using video_engine::screen;
using video_engine::OPAQUE;
using video_engine::NONE;

// Puts an item on a cell.
void Map::setItem(char item_name, Cell &position) {
  SDL_Surface **item;
  int images; // Number of different images of an item.
  bool animation = false; // If the item is animated

  // Set the varibles depending of the tipe of item.
  switch (item_name) {
    case ALTAR:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/altar", OPAQUE, NONE, 0);
      break;
    case ALTAR_EVIL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/altar-evil", OPAQUE, NONE, 0);
      break;
    case BONES:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/bones", OPAQUE, NONE, 0);
      break;
    case BONE_STACK:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/bonestack", OPAQUE, NONE, 0);
      break;
    case BOX:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/box", OPAQUE, NONE, 0);
      break;
    case BRAZIER:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/brazier", OPAQUE, NONE, 0);
      break;
    case BURIAL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/burial", OPAQUE, NONE, 0);
      break;
    case DRAGON_STATUE:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/dragonstatue", OPAQUE, NONE, 0);
      break;
    case FIRE:
      images = 8;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/fire1", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/fire2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/fire3", OPAQUE, NONE, 0);
      item[3] = screen->getImage("items/fire4", OPAQUE, NONE, 0);
      item[4] = screen->getImage("items/fire5", OPAQUE, NONE, 0);
      item[5] = screen->getImage("items/fire6", OPAQUE, NONE, 0);
      item[6] = screen->getImage("items/fire7", OPAQUE, NONE, 0);
      item[7] = screen->getImage("items/fire8", OPAQUE, NONE, 0);
      animation = true;
      break;
    case ICEPACK:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/icepack-1", OPAQUE, NONE, 0);
      break;
    case ORCISH_FLAG:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/orcish-flag", OPAQUE, NONE, 0);
      break;
    case SCARECROW:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/scarecrow", OPAQUE, NONE, 0);
      break;
    case SIGNPOST:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/signpost", OPAQUE, NONE, 0);
      break;
    case STRAW_BALE:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/straw-bale1", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/straw-bale2", OPAQUE, NONE, 0);
      break;
    case VILLAGE_CAVE:
      images = 3;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/cave", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/cave2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/cave3", OPAQUE, NONE, 0);
      break;
    case VILLAGE_COAST:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/coast", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/coast2", OPAQUE, NONE, 0);
      break;
    case VILLAGE_DESERT:
      images = 3;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/desert", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/desert2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/desert3", OPAQUE, NONE, 0);
      break;
    case VILLAGE_DESERT_CAMP:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/desert-camp", OPAQUE, NONE, 0);
      break;
    case VILLAGE_DWARF:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/dwarven", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/dwarven2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/dwarven3", OPAQUE, NONE, 0);
      item[3] = screen->getImage("items/villages/dwarven4", OPAQUE, NONE, 0);
      break;
    case VILLAGE_ELF:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/elven", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/elven2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/elven3", OPAQUE, NONE, 0);
      item[3] = screen->getImage("items/villages/elven4", OPAQUE, NONE, 0);
      break;
    case VILLAGE_ELF_SNOW:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/elven-snow", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/elven-snow2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/elven-snow3", OPAQUE, NONE, 0);
      item[3] = screen->getImage("items/villages/elven-snow4", OPAQUE, NONE, 0);
      break;
    case VILLAGE_HUMAN:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/human2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/human3", OPAQUE, NONE, 0);
      item[3] = screen->getImage("items/villages/human4", OPAQUE, NONE, 0);
      break;
    case VILLAGE_HUMAN_BURNED:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/village-human-burned1", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/village-human-burned2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/village-human-burned3", OPAQUE, NONE, 0);
      item[3] = screen->getImage("items/villages/village-human-burned4", OPAQUE, NONE, 0);
      break;
    case VILLAGE_HUMAN_CITY:
      images = 3;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human-city", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/human-city2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/human-city3", OPAQUE, NONE, 0);
      break;
    case VILLAGE_HUMAN_HILLS:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human-hills", OPAQUE, NONE, 0);
      break;
    case VILLAGE_HUMAN_SNOW:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human-snow", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/human-snow2", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/villages/human-snow3", OPAQUE, NONE, 0);
      item[3] = screen->getImage("items/villages/human-snow4", OPAQUE, NONE, 0);
      break;
    case VILLAGE_HUMAN_SNOW_HILLS:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human-snow-hills", OPAQUE, NONE, 0);
      break;
    case VILLAGE_HUT:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/hut", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/hut2", OPAQUE, NONE, 0);
      break;
    case VILLAGE_SWAMP:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/swampwater", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/villages/swampwater2", OPAQUE, NONE, 0);
      break;
    case VILLAGE_TROPICAL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/tropical-forest", OPAQUE, NONE, 0);
      break;
    case WELL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/well", OPAQUE, NONE, 0);
      break;
    case WHIRLPOOL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/whirlpool", OPAQUE, NONE, 0);
      break;
    case WINDMILL:
      images = 18;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/windmill-01", OPAQUE, NONE, 0);
      item[1] = screen->getImage("items/windmill-02", OPAQUE, NONE, 0);
      item[2] = screen->getImage("items/windmill-03", OPAQUE, NONE, 0);
      item[3] = screen->getImage("items/windmill-04", OPAQUE, NONE, 0);
      item[4] = screen->getImage("items/windmill-05", OPAQUE, NONE, 0);
      item[5] = screen->getImage("items/windmill-06", OPAQUE, NONE, 0);
      item[6] = screen->getImage("items/windmill-07", OPAQUE, NONE, 0);
      item[7] = screen->getImage("items/windmill-08", OPAQUE, NONE, 0);
      item[8] = screen->getImage("items/windmill-09", OPAQUE, NONE, 0);
      item[9] = screen->getImage("items/windmill-10", OPAQUE, NONE, 0);
      item[10] = screen->getImage("items/windmill-11", OPAQUE, NONE, 0);
      item[11] = screen->getImage("items/windmill-12", OPAQUE, NONE, 0);
      item[12] = screen->getImage("items/windmill-13", OPAQUE, NONE, 0);
      item[13] = screen->getImage("items/windmill-14", OPAQUE, NONE, 0);
      item[14] = screen->getImage("items/windmill-15", OPAQUE, NONE, 0);
      item[15] = screen->getImage("items/windmill-16", OPAQUE, NONE, 0);
      item[16] = screen->getImage("items/windmill-17", OPAQUE, NONE, 0);
      item[17] = screen->getImage("items/windmill-18", OPAQUE, NONE, 0);
      animation = true;
      break;
    default:
      std::cout << "\n\tWrong item type : " << item_name << "\n\n";
      exit(EXIT_FAILURE);
  }

  position.setItem(item_name);
  if (animation) {
    for (int i=0; i<images; i++)
      position.addSpecialImage(*item[i]);
  } else {
    int random_number;
    random_number = rand() % images;
    position.addSpecialImage(*item[random_number]);
  }

  delete [] item;
}
