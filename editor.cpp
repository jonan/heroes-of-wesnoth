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
using events_engine::MOUSE_BUTTON;
// std
using std::string;
// video_engine
using video_engine::screen;

// Constructor
Editor::Editor(const int width, const int height, const char *map_file) : Map(width, height) {
  this->map_file = strdup(map_file);

  setTerrain("flat_grass", NULL);
  editing_type = EDIT_TERRAIN;
  selected = FLAT_GRASS;
  end_editor = false;

  makeMapVisible();
}

// Destructor
Editor::~Editor(void) {
  free(map_file);
  deleteCreatures();
}

// Function to execute when the user left clicks on a cell.
void Editor::mouseLeftClick(const int x, const int y) {
  switch (editing_type) {
    case EDIT_ITEMS:
      if (map[x][y].getItemType() != selected)
        setItem(selected, map[x][y]);
      break;
    case EDIT_TERRAIN:
      if (/*map[x][y].getTerrain()*/'1' != selected)
        setTerrain(""/*selected*/, &map[x][y]);
      break;
    case EDIT_UNITS:
      delete map[x][y].getCreature();
      map[x][y].setCreature( new Unit(&selected,0) );
      break;
    default:
      // Impossible case
      break;
  }
}

// Function to execute when the user right clicks on a cell.
void Editor::mouseRightClick(const int x, const int y) {
  switch (editing_type) {
    case EDIT_ITEMS:
      if (map[x][y].getItemType() != '-')
        map[x][y].setItemType('-');
      break;
    case EDIT_UNITS:
      delete map[x][y].getCreature();
      map[x][y].setCreature(NULL);
      break;
    default:
      // Nothing to do
      break;
  }
}

// Saves the current map in the file.
void Editor::save(void) {
  // Load the files
  // Create a string with the fisical location of the map
  // "maps/" + this->map_file
  string map_dir("maps/");
  map_dir += this->map_file;
  std::ofstream map_file(map_dir.c_str());
  // "maps/" + this->map_file + "_creatures"
  string map_creatures = map_dir + "_creatures";
  std::ofstream creatures_file(map_creatures.c_str());
  // "maps/" + this->map_file + "_items"
  string map_items = map_dir + "_items";
  std::ofstream items_file(map_items.c_str());

  // Save width and height
  map_file << map_width << "\n" << map_height << "\n";
  // Save the map
  for (int y=0; y<map_height; y++) {
    for (int x=0; x<map_width; x++) {
      map_file << map[x][y].getTerrain();
      if (map[x][y].getCreature())
        creatures_file << map[x][y].getCreature()->getType();
      else
        creatures_file << '-';
      items_file << map[x][y].getItemType();
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
  // First delete current map
  deleteCreatures();
  deleteCells();
  // Load new map
  loadMapFile(map_file);
  makeMapVisible();
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
  switch (editing_type) {
    case EDIT_ITEMS:
      setTerrain("desert_road", &temp);
      setItem(selected, temp);
      break;
    case EDIT_TERRAIN:
      setTerrain("1"/*selected*/, &temp);
      break;
    case EDIT_UNITS:
      setTerrain("desert_road", &temp);
      creature = new Unit(&selected, 0);
      temp.setCreature(creature);
      break;
    default:
      // Impossible case
      break;
  }
  temp.calculateView(1);
  temp.draw(position, DRAW_TERRAIN);
  temp.draw(position, DRAW_SPECIAL_IMG);
  temp.draw(position, DRAW_UNIT);
  delete creature;
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool Editor::frame(void) {
  adjustVisibleMap();
  if (keys[SDLK_ESCAPE]) {
    keys[SDLK_ESCAPE] = false;
    end_editor = true;
  } else { // If the editor is not ended.
    if (keys[SDLK_F1]) { // save
      keys[SDLK_F1] = false;
      save();
    } else if (keys[SDLK_F2]) { // load
      keys[SDLK_F2] = false;
      load();
    } else if (keys[SDLK_F3]) { // items
      keys[SDLK_F3] = false;
      if (editing_type != EDIT_ITEMS) {
        editing_type = EDIT_ITEMS;
        selected = FIRE;
      }
    } else if (keys[SDLK_F4]) { // terrain
      keys[SDLK_F4] = false;
      if (editing_type != EDIT_TERRAIN) {
        editing_type = EDIT_TERRAIN;
        selected = FLAT_GRASS;
      }
    } else if (keys[SDLK_F5]) { // units
      keys[SDLK_F5] = false;
      if (editing_type != EDIT_UNITS) {
        editing_type = EDIT_UNITS;
        selected = '1'/*BAT*/;
      }
    }

    if (keys[SDLK_SPACE]) { // soften map
      keys[SDLK_SPACE] = false;
      softenMap();
    }

    if (mouse[MOUSE_BUTTON] == SDL_BUTTON_WHEELUP) {
      mouse[MOUSE_BUTTON] = 0;
      selected++;
      if (selected == '9'+1)
        selected = 'a';
      else if ( (selected == NUM_ITEMS    && editing_type == EDIT_ITEMS  ) ||
                (selected == NUM_TERRAINS && editing_type == EDIT_TERRAIN) ||
                (selected == '1'    && editing_type == EDIT_UNITS  )   )
        selected = '0';
    } else if (mouse[MOUSE_BUTTON] == SDL_BUTTON_WHEELDOWN) {
      mouse[MOUSE_BUTTON] = 0;
      selected--;
      if (selected == 'a'-1) {
        selected = '9';
      } else if (selected < '0') {
        if (editing_type == EDIT_ITEMS)
          selected = NUM_ITEMS - 1;
        else if (editing_type == EDIT_TERRAIN)
          selected = NUM_TERRAINS - 1;
        else if (editing_type == EDIT_UNITS)
          selected = '1' - 1;
      }
    }

    updateMouse();
    draw();
  }

  return end_editor;
}

// Starts the editor.
void startEditor(void) {
  /*Editor map(70, 50, "editor");
  map.start();*/
}
