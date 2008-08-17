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

#include "editor.hpp"

#include <fstream>
#include <string>

#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "unit.hpp"

// events_engine
using events_engine::keys;
using events_engine::mouse;
using events_engine::POSITION_X;
using events_engine::POSITION_Y;
using events_engine::BUTTON;
using events_engine::NONE;
using events_engine::WHEEL_UP;
using events_engine::WHEEL_DOWN;
// std
using std::string;
// video_engine
using video_engine::screen;

// Constructor
Editor::Editor(const int width, const int height, const char *map_file) : Map(width, height) {
  this->map_file = strdup(map_file);

  setTerrain(FLAT_GRASS, NULL);
  editing_type = TERRAINS;
  selected = FLAT_GRASS;
  end_editor = false;

  // Make the hole map visible
  for (int x=0; x<width; x++)
    for (int y=0; y<height; y++)
      battle_map[x][y].calculateView(1);
}

// Destructor
Editor::~Editor(void) {
  free(map_file);
  for (int x=0; x<width; x++)
    for (int y=0; y<height; y++)
      if (battle_map[x][y].getCreature())
        delete battle_map[x][y].getCreature();
}

// Function to execute when the user left clicks on a cell.
void Editor::mouseLeftClick(const int x, const int y) {
  if (editing_type == ITEMS) {
    if (battle_map[x][y].getItem() != selected)
      setItem(selected, battle_map[x][y]);
  } else if (editing_type == TERRAINS) {
    if (battle_map[x][y].getTerrain() != selected)
      setTerrain(selected, &battle_map[x][y]);
  } else if  (editing_type == UNITS) {
    if (battle_map[x][y].getCreature())
      delete battle_map[x][y].getCreature();
    Unit *temp = new Unit(selected, 0);
    battle_map[x][y].setCreature(temp);
  }
}

// Function to execute when the user right clicks on a cell.
void Editor::mouseRightClick(const int x, const int y) {
  if (editing_type == ITEMS) {
    if (battle_map[x][y].getItem() != '-')
      battle_map[x][y].setItem('-');
  } else if  (editing_type == UNITS) {
    if (battle_map[x][y].getCreature())
      delete battle_map[x][y].getCreature();
    battle_map[x][y].setCreature(NULL);
  }
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool Editor::frame(void) {
  Map::frame();
  if (keys[SDLK_ESCAPE]) {
    keys[SDLK_ESCAPE] = false;
    end_editor = true;
  } else { // If the editor is not ended.
    if (keys[SDLK_F1]) {
      keys[SDLK_F1] = false;
      save();
    } else if (keys[SDLK_F2]) {
      keys[SDLK_F2] = false;
      load();
    } else if (keys[SDLK_F3]) {
      keys[SDLK_F3] = false;
      if (editing_type != ITEMS) {
        editing_type = ITEMS;
        selected = FIRE;
      }
    } else if (keys[SDLK_F4]) {
      keys[SDLK_F4] = false;
      if (editing_type != TERRAINS) {
        editing_type = TERRAINS;
        selected = FLAT_GRASS;
      }
    } else if (keys[SDLK_F5]) {
      keys[SDLK_F5] = false;
      if (editing_type != UNITS) {
        editing_type = UNITS;
        selected = BAT;
      }
    }

    if (keys[SDLK_SPACE]) {
      keys[SDLK_SPACE] = false;
      softenMap();
    }

    if (mouse[BUTTON] == WHEEL_UP) {
      mouse[BUTTON] = NONE;
      selected++;
      if (selected == '9'+1)
        selected = 'a';
      else if ( (selected > LAST_ITEM && editing_type == ITEMS) ||
                (selected > LAST_TERRAIN && editing_type == TERRAINS) ||
                (selected > LAST_UNIT && editing_type == UNITS)
              )
        selected = '0';
    } else if (mouse[BUTTON] == WHEEL_DOWN) {
      mouse[BUTTON] = NONE;
      selected--;
      if (selected == 'a'-1) {
        selected = '9';
      } else if (selected < '0') {
        if (editing_type == ITEMS)
          selected = LAST_ITEM;
        else if (editing_type == TERRAINS)
          selected = LAST_TERRAIN;
        else if (editing_type == UNITS)
          selected = LAST_UNIT;
      }
    }

    moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
    draw();
  }
  return end_editor;
}

// Saves the current map in the file.
void Editor::save(void) {
  // Create a string with the fisical location of the map
  // "maps/" + name
  string map = "maps/";
  string map_name(map_file);
  string map_dir = map + map_file;
  std::ofstream map_file(map_dir.c_str());
  // "maps/" + name + "_creatures"
  string creatures = "_creatures";
  string map_creatures = map_dir + creatures;
  std::ofstream creatures_file(map_creatures.c_str());
  // "maps/" + name + "_items"
  string items = "_items";
  string map_items = map_dir + items;
  std::ofstream items_file(map_items.c_str());

  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      map_file << battle_map[x][y].getTerrain();
      if (battle_map[x][y].getCreature())
        creatures_file << battle_map[x][y].getCreature()->getType();
      else
        creatures_file << '-';
      items_file << battle_map[x][y].getItem();
    }
    map_file << '\n';
    creatures_file << '\n';
    items_file << '\n';
  }

  map_file.close();
  creatures_file.close();
  items_file.close();
}

// Loads the map from the file.
void Editor::load(void) {
  // Load the files
  // Create a string with the fisical location of the map
  // "maps/" + name
  string map = "maps/";
  string map_name(map_file);
  string map_dir = map + map_file;
  std::ifstream map_file(map_dir.c_str());
  // "maps/" + name + "_creatures"
  string creatures = "_creatures";
  string map_creatures = map_dir + creatures;
  std::ifstream creatures_file(map_creatures.c_str());
  // "maps/" + name + "_items"
  string items = "_items";
  string map_items = map_dir + items;
  std::ifstream items_file(map_items.c_str());

  if (!map_file.fail() && !creatures_file.fail() && !items_file.fail()) {
    // Delete the current map
    for (int i=0; i<width; i++)
      delete [] battle_map[i];
    delete [] battle_map;
    // The cell where the mouse was is deleted
    // so the pointer needs to be removed.
    mouse_over_cell = NULL;
    // Create a new map
    battle_map = new Cell*[width];
    for (int i=0; i<width; i++)
      battle_map[i] = new Cell[height];
    connectCells();

    char map_temp, creatures_temp, item_temp;
    int i = 0;
    int j = 0;
    while (j<height) {
      map_file.get(map_temp);
      creatures_file.get(creatures_temp);
      items_file.get(item_temp);
      // All files should have the '/n' in the
      // same position, so you only need to check one
      if (map_temp != '\n') {
        setTerrain(map_temp, &battle_map[i][j]);
        if (creatures_temp != '-') {
          Unit *creature;
          creature = new Unit(creatures_temp, 0);
          battle_map[i][j].setCreature(creature);
        }
        if (item_temp != '-')
          setItem(item_temp, battle_map[i][j]);
        i++;
        if (i == width) {
          i = 0;
          j++;
        }
      }
    }
    map_file.close();
    creatures_file.close();
    items_file.close();
    // Make the hole map visible
    for (int x=0; x<width; x++)
      for (int y=0; y<height; y++)
        battle_map[x][y].calculateView(1);
  }
}

// Draws the editor in the screen.
void Editor::draw(void) {
  Map::draw();
  screen->write("F1:save", 25, 6);
  screen->write("F2:load", 25, 20);
  screen->write("F3:items", 25, 34);
  screen->write("F4:terrain", 25, 48);
  screen->write("F5:creatures", 25, 62);
  // Temporal solution to know what terrain is selected
  SDL_Rect position;
  position.x=25;
  position.y=84;
  Cell temp;
  Unit *creature = NULL;
  if (editing_type == ITEMS) {
    setTerrain(DESERT_ROAD, &temp);
    setItem(selected, temp);
  } else if (editing_type == TERRAINS) {
    setTerrain(selected, &temp);
  } else if (editing_type == UNITS) {
    setTerrain(DESERT_ROAD, &temp);
    creature = new Unit(selected, 0);
    temp.setCreature(creature);
  }
  temp.calculateView(1);
  temp.draw(position, TERRAIN);
  temp.draw(position, SPECIAL);
  temp.draw(position, UNIT);
  if (creature) delete creature;
}

// Starts the editor.
void startEditor(void) {
  Editor map(70, 50, "editor");
  map.start();
}
