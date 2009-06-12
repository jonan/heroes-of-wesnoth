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

// video_engine
using video_engine::screen;
using video_engine::NONE;

// If position is NULL, applies the terrain to all the cells in the map.
void Map::setTerrain(char terrain_name, Cell *position) {
  // Set alpha (for all cells)
  SDL_Surface *alpha = screen->getImage("alpha", 50, NONE, 0);
  // Set stars (for all cells)
  int number_stars = 7;
  SDL_Surface **stars = new SDL_Surface*[number_stars];
  stars[0] = screen->getImage("terrain/stars/blue1");
  stars[1] = screen->getImage("terrain/stars/blue2");
  stars[2] = screen->getImage("terrain/stars/blue3");
  stars[3] = screen->getImage("terrain/stars/blue4");
  stars[4] = screen->getImage("terrain/stars/blue5");
  stars[5] = screen->getImage("terrain/stars/blue6");
  stars[6] = screen->getImage("terrain/stars/blue7");

  // Set the terrain
  SDL_Surface **terrain;
  SDL_Surface **special;
  int images_terrain; // Number of different images of a terrain.
  int images_special = 0; // Number of different special images
  bool passable = true;

  // Set the varibles depending of the tipe of terrain.
  switch (terrain_name) {
    case CAVE_FLOOR:
      images_terrain = 6;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/cave/floor");
      terrain[1] = screen->getImage("terrain/cave/floor2");
      terrain[2] = screen->getImage("terrain/cave/floor3");
      terrain[3] = screen->getImage("terrain/cave/floor4");
      terrain[4] = screen->getImage("terrain/cave/floor5");
      terrain[5] = screen->getImage("terrain/cave/floor6");
      break;
    case CAVE_HILLS:
      images_terrain = 3;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/cave/hills-variation");
      terrain[1] = screen->getImage("terrain/cave/hills-variation2");
      terrain[2] = screen->getImage("terrain/cave/hills-variation3");
      break;
    case DESERT:
      images_terrain = 8;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/desert");
      terrain[1] = screen->getImage("terrain/desert/desert2");
      terrain[2] = screen->getImage("terrain/desert/desert3");
      terrain[3] = screen->getImage("terrain/desert/desert4");
      terrain[4] = screen->getImage("terrain/desert/desert5");
      terrain[5] = screen->getImage("terrain/desert/desert6");
      terrain[6] = screen->getImage("terrain/desert/desert7");
      terrain[7] = screen->getImage("terrain/desert/desert8");
      break;
    case DESERT_HILLS:
      images_terrain = 3;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/desert-hills");
      terrain[1] = screen->getImage("terrain/desert/desert-hills2");
      terrain[2] = screen->getImage("terrain/desert/desert-hills3");
      break;
    case DESERT_MOUNTAIN:
      images_terrain = 3;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/desert-mountain-peak1");
      terrain[1] = screen->getImage("terrain/desert/desert-mountain-peak2");
      terrain[2] = screen->getImage("terrain/desert/desert-mountain-peak3");
      break;
    case DESERT_ROAD:
      images_terrain = 1;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/desert-road");
      break;
    case DESERT_SAND:
      images_terrain = 11;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/sand");
      terrain[1] = screen->getImage("terrain/desert/sand2");
      terrain[2] = screen->getImage("terrain/desert/sand3");
      terrain[3] = screen->getImage("terrain/desert/sand4");
      terrain[4] = screen->getImage("terrain/desert/sand5");
      terrain[5] = screen->getImage("terrain/desert/sand6");
      terrain[6] = screen->getImage("terrain/desert/sand7");
      terrain[7] = screen->getImage("terrain/desert/sand8");
      terrain[8] = screen->getImage("terrain/desert/sand-rock1");
      terrain[9] = screen->getImage("terrain/desert/sand-rock2");
      terrain[10] = screen->getImage("terrain/desert/sand-rock3");
      break;
    case FLAT_DIRT:
      images_terrain = 7;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/dirt");
      terrain[1] = screen->getImage("terrain/flat/dirt2");
      terrain[2] = screen->getImage("terrain/flat/dirt3");
      terrain[3] = screen->getImage("terrain/flat/dirt4");
      terrain[4] = screen->getImage("terrain/flat/dirt5");
      terrain[5] = screen->getImage("terrain/flat/dirt6");
      terrain[6] = screen->getImage("terrain/flat/dirt7");
      break;
    case FLAT_GRASS:
      images_terrain = 10;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/grass-r1");
      terrain[1] = screen->getImage("terrain/flat/grass-r2");
      terrain[2] = screen->getImage("terrain/flat/grass-r3");
      terrain[3] = screen->getImage("terrain/flat/grass-r4");
      terrain[4] = screen->getImage("terrain/flat/grass-r5");
      terrain[5] = screen->getImage("terrain/flat/grass-r6");
      terrain[6] = screen->getImage("terrain/flat/grass-r7");
      terrain[7] = screen->getImage("terrain/flat/grass-r8");
      terrain[8] = screen->getImage("terrain/flat/grass-rocks1");
      terrain[9] = screen->getImage("terrain/flat/grass-rocks2");
      break;
    case FLAT_ROAD:
      images_terrain = 3;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/road");
      terrain[1] = screen->getImage("terrain/flat/road2");
      terrain[2] = screen->getImage("terrain/flat/road3");
      break;
    case FLAT_SAVANNA:
      images_terrain = 3;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/savanna");
      terrain[1] = screen->getImage("terrain/flat/savanna2");
      terrain[2] = screen->getImage("terrain/flat/savanna3");
      break;
    case FLAT_STONE_PATH:
      images_terrain = 6;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/stone-path");
      terrain[1] = screen->getImage("terrain/flat/stone-path2");
      terrain[2] = screen->getImage("terrain/flat/stone-path3");
      terrain[3] = screen->getImage("terrain/flat/stone-path4");
      terrain[4] = screen->getImage("terrain/flat/stone-path5");
      terrain[5] = screen->getImage("terrain/flat/stone-path6");
      break;
    case FOREST_GREAT_TREE:
      images_terrain = 8;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/grass-r1");
      terrain[1] = screen->getImage("terrain/flat/grass-r2");
      terrain[2] = screen->getImage("terrain/flat/grass-r3");
      terrain[3] = screen->getImage("terrain/flat/grass-r4");
      terrain[4] = screen->getImage("terrain/flat/grass-r5");
      terrain[5] = screen->getImage("terrain/flat/grass-r6");
      terrain[6] = screen->getImage("terrain/flat/grass-r7");
      terrain[7] = screen->getImage("terrain/flat/grass-r8");
      images_special = 3;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/great-tree1");
      special[1] = screen->getImage("terrain/forest/great-tree2");
      special[2] = screen->getImage("terrain/forest/great-tree3");
      break;
    case FOREST_MUSHROOMS:
      images_terrain = 6;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/cave/floor");
      terrain[1] = screen->getImage("terrain/cave/floor2");
      terrain[2] = screen->getImage("terrain/cave/floor3");
      terrain[3] = screen->getImage("terrain/cave/floor4");
      terrain[4] = screen->getImage("terrain/cave/floor5");
      terrain[5] = screen->getImage("terrain/cave/floor6");
      images_special = 6;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/mushrooms");
      special[1] = screen->getImage("terrain/forest/mushrooms-2");
      special[2] = screen->getImage("terrain/forest/mushrooms-3");
      special[3] = screen->getImage("terrain/forest/mushrooms-4");
      special[4] = screen->getImage("terrain/forest/mushrooms-5");
      special[5] = screen->getImage("terrain/forest/mushrooms-small");
      break;
    case FOREST_PINE:
      images_terrain = 3;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/flat/savanna");
      terrain[1] = screen->getImage("terrain/flat/savanna2");
      terrain[2] = screen->getImage("terrain/flat/savanna3");
      images_special = 6;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/pine");
      special[1] = screen->getImage("terrain/forest/pine-2");
      special[2] = screen->getImage("terrain/forest/pine-3");
      special[3] = screen->getImage("terrain/forest/pine-4");
      special[4] = screen->getImage("terrain/forest/pine-small");
      special[5] = screen->getImage("terrain/forest/pine-small-2");
      break;
    case FOREST_SNOW:
      images_terrain = 2;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/snow");
      terrain[1] = screen->getImage("terrain/water/snow2");
      images_special = 5;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/snow-forest");
      special[1] = screen->getImage("terrain/forest/snow-forest-2");
      special[2] = screen->getImage("terrain/forest/snow-forest-3");
      special[3] = screen->getImage("terrain/forest/snow-forest-4");
      special[4] = screen->getImage("terrain/forest/snow-forest-small");
      break;
    case FOREST_TROPICAL:
      images_terrain = 8;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/desert/sand");
      terrain[1] = screen->getImage("terrain/desert/sand2");
      terrain[2] = screen->getImage("terrain/desert/sand3");
      terrain[3] = screen->getImage("terrain/desert/sand4");
      terrain[4] = screen->getImage("terrain/desert/sand5");
      terrain[5] = screen->getImage("terrain/desert/sand6");
      terrain[6] = screen->getImage("terrain/desert/sand7");
      terrain[7] = screen->getImage("terrain/desert/sand8");
      images_special = 4;
      special = new SDL_Surface*[images_special];
      special[0] = screen->getImage("terrain/forest/tropical");
      special[1] = screen->getImage("terrain/forest/tropical-2");
      special[2] = screen->getImage("terrain/forest/tropical-3");
      special[3] = screen->getImage("terrain/forest/tropical-4");
      break;
    case HILLS:
      images_terrain = 3;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/hills-variation");
      terrain[1] = screen->getImage("terrain/hills-variation2");
      terrain[2] = screen->getImage("terrain/hills-variation3");
      break;
    case LAVA:
      images_terrain = 3;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/lava");
      terrain[1] = screen->getImage("terrain/lava2");
      terrain[2] = screen->getImage("terrain/lava3");
      break;
    case WATER_COAST:
      images_terrain = 3;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/coast");
      terrain[1] = screen->getImage("terrain/water/coast2");
      terrain[2] = screen->getImage("terrain/water/coast3");
      break;
    case WATER_FORD:
      images_terrain = 2;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/ford");
      terrain[1] = screen->getImage("terrain/water/ford2");
      break;
    case WATER_OCEAN:
      images_terrain = 3;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/ocean");
      terrain[1] = screen->getImage("terrain/water/ocean2");
      terrain[2] = screen->getImage("terrain/water/ocean3");
      break;
    case WATER_ICE:
      images_terrain = 6;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/ice");
      terrain[1] = screen->getImage("terrain/water/ice2");
      terrain[2] = screen->getImage("terrain/water/ice3");
      terrain[3] = screen->getImage("terrain/water/ice4");
      terrain[4] = screen->getImage("terrain/water/ice5");
      terrain[5] = screen->getImage("terrain/water/ice6");
      break;
    case WATER_SNOW:
      images_terrain = 2;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/snow");
      terrain[1] = screen->getImage("terrain/water/snow2");
      break;
    case WATER_SNOW_HILLS:
      images_terrain = 3;
      passable = false;
      terrain = new SDL_Surface*[images_terrain];
      terrain[0] = screen->getImage("terrain/water/snow-hills");
      terrain[1] = screen->getImage("terrain/water/snow-hills2");
      terrain[2] = screen->getImage("terrain/water/snow-hills2");
      break;
    default:
      std::cout << "\n\tWrong terrain type : " << terrain_name << "\n\n";
      exit(EXIT_FAILURE);
  }

  int random_number;
  if (!position) { // Set the attributes to all the cells.
    for (int i=0; i<map_width; i++)
      for (int j=0; j<map_height; j++) {
        map[i][j].setAlpha(*alpha);
        random_number = rand() % number_stars;
        map[i][j].setStars(*stars[random_number]);
        random_number = rand() % images_terrain;
        map[i][j].addImage(*terrain[random_number], terrain_name);
        if (images_special>0) {
          random_number = rand() % images_special;
          map[i][j].addSpecialImage(*special[random_number]);
        }
        // If the cell is in one of the maps borders, block movement
        if ( i==0 || i==map_width-1 || j==0 || j==map_height-1)
          map[i][j].setPassable(false);
        else
          map[i][j].setPassable(passable);
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
    if ( x==0 || x==map_width-1 || y==0 || y==map_height-1)
      position->setPassable(false);
    else
      position->setPassable(passable);
  }

  delete [] stars;
  delete [] terrain;
  if (images_special) delete [] special;
}
