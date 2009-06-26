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

#include <fstream>
#include <string>

#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "unit.hpp"

// events_engine
using events_engine::input;
using events_engine::keys;
using events_engine::mouse;
using events_engine::MOUSE_X;
using events_engine::MOUSE_Y;
using events_engine::MOUSE_BUTTON;
using events_engine::ATTACK_CURSOR;
using events_engine::MOVE_CURSOR;
using events_engine::NORMAL_CURSOR;
// video_engine
using video_engine::screen;
using video_engine::FACE_RIGHT;
using video_engine::FACE_LEFT;

// Starts the map.
void Map::start(void) {
  // Set first turn.
  nextTurn();
  loop();
}

// Constructor
Map::Map(const int width, const int height) {
  map_width = width;
  map_height = height;

  // Create the array of cells
  map = new Cell*[map_width];
  for (int i=0; i<map_width; i++)
    map[i] = new Cell[map_height];
  // Set the coordinates
  for (int x=0; x<map_width; x++)
    for (int y=0; y<map_height; y++)
      map[x][y].setCoordinates(x, y);
  // Connect the cells
  connectCells();

  selected_unit = NULL;
  mouse_over_cell = NULL;

  first_cell_coor.x = 0;
  first_cell_coor.y = 0;
  // Adjust the first cell's coordinates
  first_cell_pos.x = -53;
  first_cell_pos.y = -72;

  // Calculate the size of the map's window
  window_width = window_height = 0;
  adjustVisibleMap();
}

// Constructor
Map::Map(const char *map_file) {
  loadMapFile(map_file);

  first_cell_coor.x = 0;
  first_cell_coor.y = 0;
  // Adjust the first cell's coordinates
  first_cell_pos.x = -53;
  first_cell_pos.y = -72;

  // Calculate the size of the map's window
  window_width = window_height = 0;
  adjustVisibleMap();
}

// Destructor
Map::~Map(void) {
  deleteCells();
}

// Sets the terrain type to all the cells in the map.
void Map::setTerrainToAllCells(const char *id) {
  for (int i=0; i<map_width; i++)
    for (int j=0; j<map_height; j++)
      map[i][j].setTerrain(id);
}

// Loads the terrain, creatures and items of the map from a file.
void Map::loadMapFile(const char *file_name) {
  using std::string;
  // Load the files
  // Create a string with the fisical location of the map
  // "maps/" + file_name
  string map_dir("maps/");
  map_dir += file_name;
  std::ifstream map_file(map_dir.c_str());
  // "maps/" + file_name + "_creatures"
  string map_creatures = map_dir + "_creatures";
  std::ifstream creatures_file(map_creatures.c_str());
  // "maps/" + file_name + "_items"
  string map_items = map_dir + "_items";
  std::ifstream items_file(map_items.c_str());

  if (!map_file.fail() && !creatures_file.fail() && !items_file.fail()) {
    // The cells and units haven't been created yet so there's no
    // cell with the mouse over it and there's no unit selected.
    mouse_over_cell = NULL;
    selected_unit = NULL;
    // Detect map's size
    char temp[4];
    map_file.getline(temp, 4);
    map_width = atoi(temp);
    map_file.getline(temp, 4);
    map_height = atoi(temp);
    // Create a new map
    map = new Cell*[map_width];
    for (int i=0; i<map_width; i++)
      map[i] = new Cell[map_height];
    // Set the coordinates
    for (int x=0; x<map_width; x++)
      for (int y=0; y<map_height; y++)
        map[x][y].setCoordinates(x, y);
    connectCells();

    char item_temp;
    char map_temp[3], creatures_temp[3];
    for (int j=0; j<map_height; j++) {
      for (int i=0; i<map_width; i++) {
        // Get info from file
        map_file.get(map_temp, 3);
        creatures_file.get(creatures_temp, 3);
        items_file.get(item_temp);
        // Set the info in the cell
        map[i][j].setTerrain(map_temp);
        if ( strcmp(creatures_temp, "--") ) {
          Unit *creature = new Unit(creatures_temp, 0);
          map[i][j].setCreature(creature);
        }
        if (item_temp != '-')
          setItem(item_temp, map[i][j]);
      }
      map_file.getline(map_temp, 3);
      creatures_file.getline(creatures_temp, 3);
      items_file.getline(creatures_temp, 3);
    }

    map_file.close();
    creatures_file.close();
    items_file.close();
  }
}

// Makes the hole map visible
void Map::makeMapVisible(void) {
  for (int x=0; x<map_width; x++)
    for (int y=0; y<map_height; y++)
      map[x][y].calculateView(1);
}

// Adjusts the visible map to the window size.
void Map::adjustVisibleMap(void) {
  // Calculate the size of the map's window (might have changed)
  int new_width, new_height;
  bool changed = false; // To check if the window size changed
  screen->getScreenSize(new_width, new_height);
  if (new_width != window_width) {
    changed = true;
    window_width = new_width;
    window_horizontal_cells = (window_width/108)*2+2; // +2 cells that don't fit compleatly
    if (window_horizontal_cells > map_width) window_horizontal_cells = map_width;
  }
  if (new_height != window_height) {
    changed = true;
    window_height = new_height;
    window_vertical_cells = (window_height/72)+2; // +2 cells that don't fit compleatly
    if (window_vertical_cells > map_height) window_vertical_cells = map_height;
  }
  // If the window size has change, center the view
  if (changed && selected_unit) centerView(*selected_unit);
}

// Returns a cell where the creature can attack.
Cell* Map::getAttackCell(void) {
  /// @todo Optimize this function.
  Cell *temp = NULL;
  int x, y;

  x=0;
  y=0;

  while (!temp && x<map_width) {
    if (map[x][y].canAttackHere() &&
        map[x][y].getCreature()->getMaster() != selected_unit->getMaster()) {
      temp = &map[x][y];
    } else {
      y++;
      if (y == map_height) {
        y=0;
        x++;
      }
    }
  }

  return temp;
}

// Updates the map according to the mouse state
void Map::updateMouse(void) {
  int i = first_cell_coor.x;
  int j = first_cell_coor.y;

  if (mouse_over_cell)
    mouse_over_cell->removeMouse();

  // Find out which cell is the mouse over
  SDL_Rect cellPosition;
  cellPosition.x = first_cell_pos.x;
  while (mouse[MOUSE_X] > cellPosition.x){
    cellPosition.x += 54;
    i++;
  }
  i--;
  if ( (i%2)==1 )
    cellPosition.y = first_cell_pos.y+36;
  else
    cellPosition.y = first_cell_pos.y;
  while (mouse[MOUSE_Y] > cellPosition.y){
    cellPosition.y += 72;
    j++;
  }
  j--;
  if (i>0 && i<map_width-1 && j>0 && j<map_height-1) {
    // map[i][j] is a valid cell and the mouse is over it
    map[i][j].putMouse();
    mouse_over_cell = &map[i][j];
    mouseOverCell(i,j);
    if (mouse[MOUSE_BUTTON] == SDL_BUTTON_LEFT) mouseLeftClick(i,j);
    if (mouse[MOUSE_BUTTON] == SDL_BUTTON_RIGHT) mouseRightClick(i,j);
  } else {
    input->setCursorType(NORMAL_CURSOR);
  }

  // move visible map
  if ( (mouse[MOUSE_X] == 0 || keys[SDLK_LEFT]) &&
        first_cell_coor.x != 0                        )
    first_cell_coor.x--;
  else if ( (mouse[MOUSE_X] == window_width-1 || keys[SDLK_RIGHT]) &&
             first_cell_coor.x != map_width-window_horizontal_cells      )
    first_cell_coor.x++;
  if ( (mouse[MOUSE_Y] == 0 || keys[SDLK_UP]) &&
        first_cell_coor.y != 0                      )
    first_cell_coor.y--;
  else if ( (mouse[MOUSE_Y] == window_height-1 || keys[SDLK_DOWN]) &&
             first_cell_coor.y != map_height-window_vertical_cells       )
    first_cell_coor.y++;
}

// Function to execute when the mouse is over a cell.
void Map::mouseOverCell(const int x, const int y) {
  if (map[x][y].canAttackHere() && selected_unit->getPosition() != &map[x][y])
    input->setCursorType(ATTACK_CURSOR);
  else if (map[x][y].canMoveHere())
    input->setCursorType(MOVE_CURSOR);
  else
    input->setCursorType(NORMAL_CURSOR);
}

// Function to execute when the user right clicks on a cell.
void Map::mouseRightClick(const int x, const int y) {
  centerView(map[x][y]);
  mouse[MOUSE_BUTTON] = 0;
}

// Moves the selected creature to a cell.
void Map::moveSelectedCreature(Cell &end_position) {
  int *path;
  int movements;
  Cell *temp;

  Cell* actual_position = selected_unit->getPosition();
  end_position.getPath(path, movements);

  /// @todo This isn't too elegant
  for (int i=0; i<movements; i++) {
    // Make the creature face the same direction as moving
    if (path[i] == NE || path[i] == SE) selected_unit->setFacingSide(FACE_RIGHT);
    else if (path[i] == NW || path[i] == SW) selected_unit->setFacingSide(FACE_LEFT);

    selected_unit->getPosition()->setCreature(NULL);
    temp = selected_unit->getPosition()->getConnectedCell(path[i]);
    temp->setCreature(selected_unit);
    draw();
    screen->update();
    SDL_Delay(100);
  }

  actual_position->unselect();
}

// Connects all the cells in the map.
void Map::connectCells(void) {
  for (int coor1=0; coor1<map_width; coor1++) {
    for (int coor2=0; coor2<map_height; coor2++) {
      if ( (coor1%2)==1 ) { // coor1 is an odd number
        if (coor1 == map_width-1) { // The last colum of the map
          if (coor2 == 0) {
            // map[coor1][coor2].connectCell(N, NULL);
            map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
            map[coor1][coor2].connectCell(SW, &map[coor1-1][coor2+1]);
          } else if (coor2 == map_height-1) {
            map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
            // map[coor1][coor2].connectCell(S, NULL);
            // map[coor1][coor2].connectCell(SW, NULL);
          } else {
            map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
            map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
            map[coor1][coor2].connectCell(SW, &map[coor1-1][coor2+1]);
          }
          // map[coor1][coor2].connectCell(NE, NULL);
          // map[coor1][coor2].connectCell(SE, NULL);
          map[coor1][coor2].connectCell(NW, &map[coor1-1][coor2]);
        } else if (coor2 == 0) { // The first row of the map
          // map[coor1][coor2].connectCell(N, NULL);
          map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
          map[coor1][coor2].connectCell(NE, &map[coor1+1][coor2]);
          map[coor1][coor2].connectCell(SE, &map[coor1+1][coor2+1]);
          map[coor1][coor2].connectCell(NW, &map[coor1-1][coor2]);
          map[coor1][coor2].connectCell(SW, &map[coor1-1][coor2+1]);
        } else if (coor2 == map_height-1) { // Last row of the map
          map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
          // map[coor1][coor2].connectCell(S, NULL);
          map[coor1][coor2].connectCell(NE, &map[coor1+1][coor2]);
          // map[coor1][coor2].connectCell(SE, NULL);
          map[coor1][coor2].connectCell(NW, &map[coor1-1][coor2]);
          // map[coor1][coor2].connectCell(SW, NULL);
        } else {
          map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
          map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
          map[coor1][coor2].connectCell(NE, &map[coor1+1][coor2]);
          map[coor1][coor2].connectCell(SE, &map[coor1+1][coor2+1]);
          map[coor1][coor2].connectCell(NW, &map[coor1-1][coor2]);
          map[coor1][coor2].connectCell(SW, &map[coor1-1][coor2+1]);
        }
      } else { // coor1 is an even number
        if (coor1 == 0) { // The first colum of the map
          if (coor2 == 0) {
            // map[coor1][coor2].connectCell(N, NULL);
            map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
            // map[coor1][coor2].connectCell(NE, NULL);
          } else if (coor2 == map_height-1) {
            map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
            // map[coor1][coor2].connectCell(S, NULL);
            map[coor1][coor2].connectCell(NE, &map[coor1+1][coor2-1]);
          } else {
            map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
            map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
            map[coor1][coor2].connectCell(NE, &map[coor1+1][coor2-1]);
          }
          // map[coor1][coor2].connectCell(NW, NULL);
          // map[coor1][coor2].connectCell(SW, NULL);
          map[coor1][coor2].connectCell(SE, &map[coor1+1][coor2]);
        } else if (coor1 == map_width-1) { // The last colum of the map
          if (coor2 == 0) {
            // map[coor1][coor2].connectCell(N, NULL);
            map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
            // map[coor1][coor2].connectCell(NW, NULL);
          } else if (coor2 == map_height-1) {
            map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
            // map[coor1][coor2].connectCell(S, NULL);
            map[coor1][coor2].connectCell(NW,&map[coor1-1][coor2-1]);
          } else {
            map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
            map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
            map[coor1][coor2].connectCell(NW, &map[coor1-1][coor2-1]);
          }
          // map[coor1][coor2].connectCell(NE, NULL);
          // map[coor1][coor2].connectCell(SE, NULL);
          map[coor1][coor2].connectCell(SW, &map[coor1-1][coor2]);
        } else if (coor2 == 0) { // The first row of the map
          //  map[coor1][coor2].connectCell(N, NULL);
          map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
          // map[coor1][coor2].connectCell(NE, NULL);
          map[coor1][coor2].connectCell(SE, &map[coor1+1][coor2]);
          // map[coor1][coor2].connectCell(NW, NULL);
          map[coor1][coor2].connectCell(SW, &map[coor1-1][coor2]);
        } else if (coor2 == map_height-1) { // Last row of the map
          map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
          // map[coor1][coor2].connectCell(S, NULL);
          map[coor1][coor2].connectCell(NE, &map[coor1+1][coor2-1]);
          map[coor1][coor2].connectCell(SE, &map[coor1+1][coor2]);
          map[coor1][coor2].connectCell(NW, &map[coor1-1][coor2-1]);
          map[coor1][coor2].connectCell(SW, &map[coor1-1][coor2]);
        } else {
          map[coor1][coor2].connectCell(N, &map[coor1][coor2-1]);
          map[coor1][coor2].connectCell(S, &map[coor1][coor2+1]);
          map[coor1][coor2].connectCell(NE, &map[coor1+1][coor2-1]);
          map[coor1][coor2].connectCell(SE, &map[coor1+1][coor2]);
          map[coor1][coor2].connectCell(NW, &map[coor1-1][coor2-1]);
          map[coor1][coor2].connectCell(SW, &map[coor1-1][coor2]);
        }
      }
    }
  }
}

// Centers the map view in a given cell
void Map::centerView(Cell& position) {
  int x, y;
  position.getCoordinates(x, y);

  x -= window_horizontal_cells/2;
  y -= window_vertical_cells/2;
  if (x<0) x=0;
  if (y<0) y=0;
  if (map_width-x < window_horizontal_cells) x -= window_horizontal_cells-(map_width-x);
  if (map_height-y < window_vertical_cells) y -= window_vertical_cells-(map_height-y);

  first_cell_coor.x = x;
  first_cell_coor.y = y;
}

// Centers the map view in a given creature
void Map::centerView(Unit& creature) {
  centerView(*creature.getPosition());
}

// Draws the map in the screen.
void Map::draw(void) {
  SDL_Rect position;

  screen->erase();
  // Draws the visible cells.
  for (int i=DRAW_TERRAIN; i<=DRAW_UNIT; i++) {
    // Position of the firts cell (top-left)
    position.x = first_cell_pos.x;
    if ( (first_cell_coor.x%2)==1 )
      position.y = first_cell_pos.y+36;
    else
      position.y = first_cell_pos.y;
    position.w = 72;
    position.h = 72;
    // Draw
    for (int x=first_cell_coor.x; position.x<window_width && x<map_width; x++) {
      for (int y=first_cell_coor.y; position.y<window_height && y<map_height; y++) {
        map[x][y].draw(position, i);
        position.y+=72;
      }
      if ( (x%2)==1 ) // x is an odd number
        position.y=first_cell_pos.y;
      else
        position.y=first_cell_pos.y+36;
      position.x+=54;
    }
  }
}

// Delete all the cells of the map
void Map::deleteCells(void) {
  for (int i=0; i<map_width; i++)
    delete [] map[i];
  delete [] map;
}

// Delete all the creatures in the map
void Map::deleteCreatures(void) {
  for (int x=0; x<map_width; x++)
    for (int y=0; y<map_height; y++) {
      delete map[x][y].getCreature();
      map[x][y].setCreature(NULL);
    }
}
