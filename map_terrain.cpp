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

#include "map.hpp"

#include <cstdlib>
#include <iostream>

#include <SDL/SDL.h>

#include "cell.hpp"
#include "graphics.hpp"

// video_engine
using video_engine::screen;

using video_engine::OPAQUE;

using video_engine::NONE;

// Indicates the terrain image of the map. Specify only the terrain_name
// attribute to apply the terrain to all the cells of the map.
void Map::setTerrain(const char terrain_name, const int x, const int y) {
  // Set alpha (for all cells)
  SDL_Surface *alpha = screen->getImage("alpha", 50, NONE, 0);
  // Set stars (for all cells)
  int number_stars = 7;
  SDL_Surface **stars = new SDL_Surface*[number_stars];
  stars[0] = screen->getImage("terrain/stars/blue1", OPAQUE, NONE, 0);
  stars[1] = screen->getImage("terrain/stars/blue2", OPAQUE, NONE, 0);
  stars[2] = screen->getImage("terrain/stars/blue3", OPAQUE, NONE, 0);
  stars[3] = screen->getImage("terrain/stars/blue4", OPAQUE, NONE, 0);
  stars[4] = screen->getImage("terrain/stars/blue5", OPAQUE, NONE, 0);
  stars[5] = screen->getImage("terrain/stars/blue6", OPAQUE, NONE, 0);
  stars[6] = screen->getImage("terrain/stars/blue7", OPAQUE, NONE, 0);

  // Set the terrain
  SDL_Surface **terrain;
  int images; // Number of different images of a terrain.
  int movement_penalty;

  // Set the varibles depending of the tipe of terrain.
  switch (terrain_name) {
    case CAVE_FLOOR:
      images = 6;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/cave/floor", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/cave/floor2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/cave/floor3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/cave/floor4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/cave/floor5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/cave/floor6", OPAQUE, NONE, 0);
      break;
    case CAVE_HILLS:
      images = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/cave/hills-variation", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/cave/hills-variation2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/cave/hills-variation3", OPAQUE, NONE, 0);
      break;
    case DESERT:
      images = 8;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/desert", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/desert/desert2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/desert/desert3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/desert/desert4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/desert/desert5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/desert/desert6", OPAQUE, NONE, 0);
      terrain[6] = screen->getImage("terrain/desert/desert7", OPAQUE, NONE, 0);
      terrain[7] = screen->getImage("terrain/desert/desert8", OPAQUE, NONE, 0);
      break;
    case DESERT_HILLS:
      images = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/desert-hills", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/desert/desert-hills2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/desert/desert-hills3", OPAQUE, NONE, 0);
      break;
    case DESERT_MOUNTAIN:
      images = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/desert-mountain-peak1", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/desert/desert-mountain-peak2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/desert/desert-mountain-peak3", OPAQUE, NONE, 0);
      break;
    case DESERT_ROAD:
      images = 1;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/desert-road", OPAQUE, NONE, 0);
      break;
    case DESERT_SAND:
      images = 8;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/desert/sand", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/desert/sand2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/desert/sand3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/desert/sand4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/desert/sand5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/desert/sand6", OPAQUE, NONE, 0);
      terrain[6] = screen->getImage("terrain/desert/sand7", OPAQUE, NONE, 0);
      terrain[7] = screen->getImage("terrain/desert/sand8", OPAQUE, NONE, 0);
      break;
    case FLAT_DIRT:
      images = 1;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/dirt", OPAQUE, NONE, 0);
      break;
    case FLAT_GRASS:
      images = 8;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/grass-r1", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/grass-r2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/grass-r3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/flat/grass-r4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/flat/grass-r5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/flat/grass-r6", OPAQUE, NONE, 0);
      terrain[6] = screen->getImage("terrain/flat/grass-r7", OPAQUE, NONE, 0);
      terrain[7] = screen->getImage("terrain/flat/grass-r8", OPAQUE, NONE, 0);
      break;
    case FLAT_ROAD:
      images = 3;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/road", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/road2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/road3", OPAQUE, NONE, 0);
      break;
    case FLAT_SAVANNA:
      images = 3;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/savanna", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/savanna2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/savanna3", OPAQUE, NONE, 0);
      break;
    case FLAT_STONE_PATH:
      images = 6;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/flat/stone-path", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/stone-path2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/stone-path3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/flat/stone-path4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/flat/stone-path5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/flat/stone-path6", OPAQUE, NONE, 0);
      break;
    case HILLS:
      images = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/hills-variation", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/hills-variation2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/hills-variation3", OPAQUE, NONE, 0);
      break;
    case LAVA:
      images = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/lava", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/lava2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/lava3", OPAQUE, NONE, 0);
      break;
    case WATER_COAST:
      images = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/coast", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/coast2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/water/coast3", OPAQUE, NONE, 0);
      break;
    case WATER_FORD:
      images = 2;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/ford", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/ford2", OPAQUE, NONE, 0);
      break;
    case WATER_OCEAN:
      images = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/ocean", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/ocean2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/water/ocean3", OPAQUE, NONE, 0);
      break;
    case WATER_ICE:
      images = 6;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/ice", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/ice2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/water/ice3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/water/ice4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/water/ice5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/water/ice6", OPAQUE, NONE, 0);
      break;
    case WATER_SNOW:
      images = 2;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/snow", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/snow2", OPAQUE, NONE, 0);
      break;
    case WATER_SNOW_HILLS:
      images = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images];
      terrain[0] = screen->getImage("terrain/water/snow-hills", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/snow-hills2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/water/snow-hills2", OPAQUE, NONE, 0);
      break;
    default:
      std::cout << "\n\tWrong terrain type : " << terrain_name << "\n\n";
      exit(EXIT_FAILURE);
  }

  int random_number;
  if (x == -1 && y ==-1) { // Set the attributes to all the cells.
    for (int i=0; i<width; i++)
      for (int j=0; j<height; j++) {
        battle_map[i][j].setAlpha(*alpha);
        random_number = rand() % number_stars;
        battle_map[i][j].setStars(*stars[random_number]);
        random_number = rand() % images;
        battle_map[i][j].addImage(*terrain[random_number], terrain_name);
        battle_map[i][j].setMovementPenalty(movement_penalty);
      }
  } else { // Set the attributes to a given cell.
    battle_map[x][y].setAlpha(*alpha);
    random_number = rand() % number_stars;
    battle_map[x][y].setStars(*stars[random_number]);
    random_number = rand() % images;
    battle_map[x][y].addImage(*terrain[random_number], terrain_name);
    battle_map[x][y].setMovementPenalty(movement_penalty);
  }
}
