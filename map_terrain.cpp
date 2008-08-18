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

// If position is NULL, applies the terrain to all the cells in the map.
void Map::setTerrain(char terrain_name, Cell *position) {
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
  SDL_Surface **special;
  int images_terrain; // Number of different images of a terrain.
  int images_special = 0; // Number of different special images
  int movement_penalty;

  // Set the varibles depending of the tipe of terrain.
  switch (terrain_name) {
    case CAVE_FLOOR:
      images_terrain = 6;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/cave/floor", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/cave/floor2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/cave/floor3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/cave/floor4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/cave/floor5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/cave/floor6", OPAQUE, NONE, 0);
      break;
    case CAVE_HILLS:
      images_terrain = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/cave/hills-variation", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/cave/hills-variation2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/cave/hills-variation3", OPAQUE, NONE, 0);
      break;
    case DESERT:
      images_terrain = 8;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
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
      images_terrain = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/desert-hills", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/desert/desert-hills2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/desert/desert-hills3", OPAQUE, NONE, 0);
      break;
    case DESERT_MOUNTAIN:
      images_terrain = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/desert-mountain-peak1", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/desert/desert-mountain-peak2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/desert/desert-mountain-peak3", OPAQUE, NONE, 0);
      break;
    case DESERT_ROAD:
      images_terrain = 1;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/desert-road", OPAQUE, NONE, 0);
      break;
    case DESERT_SAND:
      images_terrain = 11;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/sand", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/desert/sand2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/desert/sand3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/desert/sand4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/desert/sand5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/desert/sand6", OPAQUE, NONE, 0);
      terrain[6] = screen->getImage("terrain/desert/sand7", OPAQUE, NONE, 0);
      terrain[7] = screen->getImage("terrain/desert/sand8", OPAQUE, NONE, 0);
      terrain[8] = screen->getImage("terrain/desert/sand-rock1", OPAQUE, NONE, 0);
      terrain[9] = screen->getImage("terrain/desert/sand-rock2", OPAQUE, NONE, 0);
      terrain[10] = screen->getImage("terrain/desert/sand-rock3", OPAQUE, NONE, 0);
      break;
    case FLAT_DIRT:
      images_terrain = 1;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/dirt", OPAQUE, NONE, 0);
      break;
    case FLAT_GRASS:
      images_terrain = 10;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/grass-r1", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/grass-r2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/grass-r3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/flat/grass-r4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/flat/grass-r5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/flat/grass-r6", OPAQUE, NONE, 0);
      terrain[6] = screen->getImage("terrain/flat/grass-r7", OPAQUE, NONE, 0);
      terrain[7] = screen->getImage("terrain/flat/grass-r8", OPAQUE, NONE, 0);
      terrain[8] = screen->getImage("terrain/flat/grass-rocks1", OPAQUE, NONE, 0);
      terrain[9] = screen->getImage("terrain/flat/grass-rocks2", OPAQUE, NONE, 0);
      break;
    case FLAT_ROAD:
      images_terrain = 3;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/road", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/road2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/road3", OPAQUE, NONE, 0);
      break;
    case FLAT_SAVANNA:
      images_terrain = 3;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/savanna", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/savanna2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/savanna3", OPAQUE, NONE, 0);
      break;
    case FLAT_STONE_PATH:
      images_terrain = 6;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/stone-path", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/stone-path2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/stone-path3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/flat/stone-path4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/flat/stone-path5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/flat/stone-path6", OPAQUE, NONE, 0);
      break;
    case FOREST_GREAT_TREE:
      images_terrain = 8;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/grass-r1", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/grass-r2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/grass-r3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/flat/grass-r4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/flat/grass-r5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/flat/grass-r6", OPAQUE, NONE, 0);
      terrain[6] = screen->getImage("terrain/flat/grass-r7", OPAQUE, NONE, 0);
      terrain[7] = screen->getImage("terrain/flat/grass-r8", OPAQUE, NONE, 0);
      images_special = 3;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/great-tree1", OPAQUE, NONE, 0);
      special[1] = screen->getImage("terrain/forest/great-tree2", OPAQUE, NONE, 0);
      special[2] = screen->getImage("terrain/forest/great-tree3", OPAQUE, NONE, 0);
      break;
    case FOREST_MUSHROOMS:
      images_terrain = 6;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/cave/floor", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/cave/floor2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/cave/floor3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/cave/floor4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/cave/floor5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/cave/floor6", OPAQUE, NONE, 0);
      images_special = 6;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/mushrooms", OPAQUE, NONE, 0);
      special[1] = screen->getImage("terrain/forest/mushrooms-2", OPAQUE, NONE, 0);
      special[2] = screen->getImage("terrain/forest/mushrooms-3", OPAQUE, NONE, 0);
      special[3] = screen->getImage("terrain/forest/mushrooms-4", OPAQUE, NONE, 0);
      special[4] = screen->getImage("terrain/forest/mushrooms-5", OPAQUE, NONE, 0);
      special[5] = screen->getImage("terrain/forest/mushrooms-small", OPAQUE, NONE, 0);
      break;
    case FOREST_PINE:
      images_terrain = 3;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/savanna", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/flat/savanna2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/flat/savanna3", OPAQUE, NONE, 0);
      images_special = 6;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/pine", OPAQUE, NONE, 0);
      special[1] = screen->getImage("terrain/forest/pine-2", OPAQUE, NONE, 0);
      special[2] = screen->getImage("terrain/forest/pine-3", OPAQUE, NONE, 0);
      special[3] = screen->getImage("terrain/forest/pine-4", OPAQUE, NONE, 0);
      special[4] = screen->getImage("terrain/forest/pine-small", OPAQUE, NONE, 0);
      special[5] = screen->getImage("terrain/forest/pine-small-2", OPAQUE, NONE, 0);
      break;
    case FOREST_SNOW:
      images_terrain = 2;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/snow", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/snow2", OPAQUE, NONE, 0);
      images_special = 5;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/snow-forest", OPAQUE, NONE, 0);
      special[1] = screen->getImage("terrain/forest/snow-forest-2", OPAQUE, NONE, 0);
      special[2] = screen->getImage("terrain/forest/snow-forest-3", OPAQUE, NONE, 0);
      special[3] = screen->getImage("terrain/forest/snow-forest-4", OPAQUE, NONE, 0);
      special[4] = screen->getImage("terrain/forest/snow-forest-small", OPAQUE, NONE, 0);
      break;
    case FOREST_TROPICAL:
      images_terrain = 8;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/sand", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/desert/sand2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/desert/sand3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/desert/sand4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/desert/sand5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/desert/sand6", OPAQUE, NONE, 0);
      terrain[6] = screen->getImage("terrain/desert/sand7", OPAQUE, NONE, 0);
      terrain[7] = screen->getImage("terrain/desert/sand8", OPAQUE, NONE, 0);
      images_special = 4;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/tropical", OPAQUE, NONE, 0);
      special[1] = screen->getImage("terrain/forest/tropical-2", OPAQUE, NONE, 0);
      special[2] = screen->getImage("terrain/forest/tropical-3", OPAQUE, NONE, 0);
      special[3] = screen->getImage("terrain/forest/tropical-4", OPAQUE, NONE, 0);
      break;
    case HILLS:
      images_terrain = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/hills-variation", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/hills-variation2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/hills-variation3", OPAQUE, NONE, 0);
      break;
    case LAVA:
      images_terrain = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/lava", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/lava2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/lava3", OPAQUE, NONE, 0);
      break;
    case WATER_COAST:
      images_terrain = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/coast", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/coast2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/water/coast3", OPAQUE, NONE, 0);
      break;
    case WATER_FORD:
      images_terrain = 2;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/ford", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/ford2", OPAQUE, NONE, 0);
      break;
    case WATER_OCEAN:
      images_terrain = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/ocean", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/ocean2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/water/ocean3", OPAQUE, NONE, 0);
      break;
    case WATER_ICE:
      images_terrain = 6;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/ice", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/ice2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/water/ice3", OPAQUE, NONE, 0);
      terrain[3] = screen->getImage("terrain/water/ice4", OPAQUE, NONE, 0);
      terrain[4] = screen->getImage("terrain/water/ice5", OPAQUE, NONE, 0);
      terrain[5] = screen->getImage("terrain/water/ice6", OPAQUE, NONE, 0);
      break;
    case WATER_SNOW:
      images_terrain = 2;
      movement_penalty = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/snow", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/snow2", OPAQUE, NONE, 0);
      break;
    case WATER_SNOW_HILLS:
      images_terrain = 3;
      movement_penalty = 1000;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/snow-hills", OPAQUE, NONE, 0);
      terrain[1] = screen->getImage("terrain/water/snow-hills2", OPAQUE, NONE, 0);
      terrain[2] = screen->getImage("terrain/water/snow-hills2", OPAQUE, NONE, 0);
      break;
    default:
      std::cout << "\n\tWrong terrain type : " << terrain_name << "\n\n";
      exit(EXIT_FAILURE);
  }

  int random_number;
  if (!position) { // Set the attributes to all the cells.
    for (int i=0; i<width; i++)
      for (int j=0; j<height; j++) {
        battle_map[i][j].setAlpha(*alpha);
        random_number = rand() % number_stars;
        battle_map[i][j].setStars(*stars[random_number]);
        random_number = rand() % images_terrain;
        battle_map[i][j].addImage(*terrain[random_number], terrain_name);
        if (images_special>0) {
          random_number = rand() % images_special;
          battle_map[i][j].addSpecialImage(*special[random_number]);
        }
        // If the cell is in one of the maps borders, block movement
        if ( i==0 || i==width-1 || j==0 || j==height-1)
          battle_map[i][j].setMovementPenalty(1000);
        else
          battle_map[i][j].setMovementPenalty(movement_penalty);
      }
  } else { // Set the attributes to a given cell.
    position->setAlpha(*alpha);
    random_number = rand() % number_stars;
    position->setStars(*stars[random_number]);
    random_number = rand() % images_terrain;
    position->addImage(*terrain[random_number], terrain_name);
    if (images_special>0) {
      random_number = rand() % images_special;
      position->addSpecialImage(*special[random_number]);
    }
    // If the cell is in one of the maps borders, block movement
    int x, y;
    position->getCoordinates(x, y);
    if ( x==0 || x==width-1 || y==0 || y==height-1)
      position->setMovementPenalty(1000);
    else
      position->setMovementPenalty(movement_penalty);
  }

  delete [] stars;
  delete [] terrain;
  if (images_special) delete [] special;
}
