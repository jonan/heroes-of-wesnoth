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

#include "editor.hpp"

#include <fstream>

#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"

// events_engine
using events_engine::keys;
using events_engine::mouse;

using events_engine::POSITION_X;
using events_engine::POSITION_Y;
using events_engine::BUTTON;

using events_engine::NONE;
using events_engine::WHEEL_UP;
using events_engine::WHEEL_DOWN;

// video_engine
using video_engine::screen;

// Constructor
Editor::Editor(const int width, const int height) : Map(width, height) {
  setTerrain(FLAT_GRASS, -1, -1);
  actual_terrain = FLAT_GRASS;
  end_editor = false;

  // Make the hole map visible
  for (int x=0; x<width; x++)
    for (int y=0; y<height; y++)
      battle_map[x][y].calculateView(1);
}

// Function to execute when the user clicks on a cell.
void Editor::mouseClick(const int x, const int y) {
  if (battle_map[x][y].getTerrain() != actual_terrain)
    setTerrain(actual_terrain, x, y);
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool Editor::frame(void) {
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
    }

    if (keys[SDLK_SPACE]) {
      keys[SDLK_SPACE] = false;
      softenMap();
    }

    if (mouse[BUTTON] == WHEEL_UP) {
      mouse[BUTTON] = NONE;
      actual_terrain++;
      if (actual_terrain == '9'+1) actual_terrain = 'a';
      else if (actual_terrain > LAST_TERRAIN) actual_terrain = '0';
    } else if (mouse[BUTTON] == WHEEL_DOWN) {
      mouse[BUTTON] = NONE;
      actual_terrain--;
      if (actual_terrain == 'a'-1) actual_terrain = '9';
      else if (actual_terrain < '0') actual_terrain = LAST_TERRAIN;
    }

    moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
    draw();
  }
  return end_editor;
}

// Saves the current map in the file.
void Editor::save(void) {
  std::ofstream file("maps/editor");

  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++)
      file << battle_map[x][y].getTerrain();
    file << '\n';
  }

  file.close();
}

// Loads the map from the file.
void Editor::load(void) {
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
  // Load the file
  std::ifstream file("maps/editor");
  char temp;
  int i = 0;
  int j = 0;
  while (j<height) {
    file.get(temp);
    if (temp != '\n') {
      setTerrain(temp, i, j);
      i++;
      if (i == width) {
        i = 0;
        j++;
      }
    }
  }
  file.close();
  // Make the hole map visible
  for (int x=0; x<width; x++)
    for (int y=0; y<height; y++)
      battle_map[x][y].calculateView(1);
}

// Draws the editor in the screen.
void Editor::draw(void) {
  Map::draw();
  screen->write("F1:save", 25, 6);
  screen->write("F2:load", 25, 20);
  // Temporal solution to know what terrain is selected
  /// @todo Erase this when a better method is implemented.
  /// Remember to DISALLOW_COPY_AND_ASSIGN in cell.
  SDL_Rect position;
  position.x=503;
  position.y=-40;
  Cell terrain, temp;
  temp = battle_map[0][0];
  setTerrain(actual_terrain, 0, 0);
  terrain = battle_map[0][0];
  battle_map[0][0] = temp;
  terrain.draw(position);
}

// Starts the editor.
void startEditor(void) {
  Editor map(30,20);
  map.start();
}
