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

#include "map.hpp"

#include <cstdlib>
#include <iostream>

#include "cell.hpp"
#include "graphics.hpp"

using video_engine::screen;

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
      item[0] = screen->getImage("items/altar");
      break;
    case ALTAR_EVIL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/altar-evil");
      break;
    case BONES:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/bones");
      break;
    case BONE_STACK:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/bonestack");
      break;
    case BOX:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/box");
      break;
    case BRAZIER:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/brazier");
      break;
    case BRAZIER_LIT:
      images = 8;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/brazier-lit1");
      item[1] = screen->getImage("items/brazier-lit2");
      item[2] = screen->getImage("items/brazier-lit3");
      item[3] = screen->getImage("items/brazier-lit4");
      item[4] = screen->getImage("items/brazier-lit5");
      item[5] = screen->getImage("items/brazier-lit6");
      item[6] = screen->getImage("items/brazier-lit7");
      item[7] = screen->getImage("items/brazier-lit8");
      animation = true;
      break;
    case BURIAL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/burial");
      break;
    case DRAGON_STATUE:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/dragonstatue");
      break;
    case FIRE:
      images = 8;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/fire1");
      item[1] = screen->getImage("items/fire2");
      item[2] = screen->getImage("items/fire3");
      item[3] = screen->getImage("items/fire4");
      item[4] = screen->getImage("items/fire5");
      item[5] = screen->getImage("items/fire6");
      item[6] = screen->getImage("items/fire7");
      item[7] = screen->getImage("items/fire8");
      animation = true;
      break;
    case ICEPACK:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/icepack-1");
      break;
    case ORCISH_FLAG:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/orcish-flag");
      break;
    case SCARECROW:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/scarecrow");
      break;
    case SIGNPOST:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/signpost");
      break;
    case STRAW_BALE:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/straw-bale1");
      item[1] = screen->getImage("items/straw-bale2");
      break;
    case VILLAGE_CAVE:
      images = 3;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/cave");
      item[1] = screen->getImage("items/villages/cave2");
      item[2] = screen->getImage("items/villages/cave3");
      break;
    case VILLAGE_COAST:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/coast");
      item[1] = screen->getImage("items/villages/coast2");
      break;
    case VILLAGE_DESERT:
      images = 3;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/desert");
      item[1] = screen->getImage("items/villages/desert2");
      item[2] = screen->getImage("items/villages/desert3");
      break;
    case VILLAGE_DESERT_CAMP:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/desert-camp");
      break;
    case VILLAGE_DWARF:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/dwarven");
      item[1] = screen->getImage("items/villages/dwarven2");
      item[2] = screen->getImage("items/villages/dwarven3");
      item[3] = screen->getImage("items/villages/dwarven4");
      break;
    case VILLAGE_ELF:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/elven");
      item[1] = screen->getImage("items/villages/elven2");
      item[2] = screen->getImage("items/villages/elven3");
      item[3] = screen->getImage("items/villages/elven4");
      break;
    case VILLAGE_ELF_SNOW:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/elven-snow");
      item[1] = screen->getImage("items/villages/elven-snow2");
      item[2] = screen->getImage("items/villages/elven-snow3");
      item[3] = screen->getImage("items/villages/elven-snow4");
      break;
    case VILLAGE_HUMAN:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human");
      item[1] = screen->getImage("items/villages/human2");
      item[2] = screen->getImage("items/villages/human3");
      item[3] = screen->getImage("items/villages/human4");
      break;
    case VILLAGE_HUMAN_BURNED:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/village-human-burned1");
      item[1] = screen->getImage("items/villages/village-human-burned2");
      item[2] = screen->getImage("items/villages/village-human-burned3");
      item[3] = screen->getImage("items/villages/village-human-burned4");
      break;
    case VILLAGE_HUMAN_CITY:
      images = 3;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human-city");
      item[1] = screen->getImage("items/villages/human-city2");
      item[2] = screen->getImage("items/villages/human-city3");
      break;
    case VILLAGE_HUMAN_HILLS:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human-hills");
      break;
    case VILLAGE_HUMAN_SNOW:
      images = 4;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human-snow");
      item[1] = screen->getImage("items/villages/human-snow2");
      item[2] = screen->getImage("items/villages/human-snow3");
      item[3] = screen->getImage("items/villages/human-snow4");
      break;
    case VILLAGE_HUMAN_SNOW_HILLS:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/human-snow-hills");
      break;
    case VILLAGE_HUT:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/hut");
      item[1] = screen->getImage("items/villages/hut2");
      break;
    case VILLAGE_HUT_SNOW:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/hut-snow");
      item[1] = screen->getImage("items/villages/hut-snow2");
      break;
    case VILLAGE_SWAMP:
      images = 2;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/swampwater");
      item[1] = screen->getImage("items/villages/swampwater2");
      break;
    case VILLAGE_TROPICAL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/villages/tropical-forest");
      break;
    case WELL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/well");
      break;
    case WHIRLPOOL:
      images = 1;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/whirlpool");
      break;
    case WINDMILL:
      images = 18;
      item = new SDL_Surface*[images];
      item[0] = screen->getImage("items/windmill-01");
      item[1] = screen->getImage("items/windmill-02");
      item[2] = screen->getImage("items/windmill-03");
      item[3] = screen->getImage("items/windmill-04");
      item[4] = screen->getImage("items/windmill-05");
      item[5] = screen->getImage("items/windmill-06");
      item[6] = screen->getImage("items/windmill-07");
      item[7] = screen->getImage("items/windmill-08");
      item[8] = screen->getImage("items/windmill-09");
      item[9] = screen->getImage("items/windmill-10");
      item[10] = screen->getImage("items/windmill-11");
      item[11] = screen->getImage("items/windmill-12");
      item[12] = screen->getImage("items/windmill-13");
      item[13] = screen->getImage("items/windmill-14");
      item[14] = screen->getImage("items/windmill-15");
      item[15] = screen->getImage("items/windmill-16");
      item[16] = screen->getImage("items/windmill-17");
      item[17] = screen->getImage("items/windmill-18");
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
