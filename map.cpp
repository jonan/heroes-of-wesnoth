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

#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "timer.hpp"
#include "unit.hpp"

// events_engine
using events_engine::input;
using events_engine::keys;

using events_engine::BUTTON_LEFT;

// video_engine
using video_engine::screen;

using video_engine::RIGHT;
using video_engine::LEFT;

// Starts the map.
void Map::start(void) {
  // Set first turn.
  nextTurn();

  /// @todo Use the loop function in loop.hpp
  bool done = false;
  Timer fps;

  while (!done) {
    fps.start();
    input->readInput();
    done = frame();
    screen->update();
    fps.end(30);
  }
}

// Constructor
Map::Map(const int width, const int height) {
  this->width = width;
  this->height = height;

  // Create the array of cells
  battle_map = new Cell*[width];
  for (int i=0; i<width; i++)
    battle_map[i] = new Cell[height];

  connectCells();

  for (int x=0; x<width; x++)
    for (int y=0; y<height; y++)
      battle_map[x][y].setCoordinates(x, y);

  first_cell_coor.x = 0;
  first_cell_coor.y = 0;
  // Calculate the size of the visible map
  int screen_width, screen_height;
  screen->getScreenSize(screen_width, screen_height);
  horizontal_cells = (screen_width/54);
  vertical_cells = (screen_height/72)-1;
  if (horizontal_cells > width) horizontal_cells = width;
  if (vertical_cells > height) vertical_cells = height;
  // Center the map in the screen
  first_cell_pos.x = (screen_width-(horizontal_cells*54+18))/2;
  first_cell_pos.y = (screen_height-(vertical_cells*72+36))/2;

  selected_unit=NULL;
  mouse_over_cell=NULL;
}

// Destructor
Map::~Map(void) {
  for (int i=0; i<width; i++)
    delete [] battle_map[i];
  delete [] battle_map;
}

// Returns a cell where the creature can attack.
Cell* Map::getAttackCell(void) {
  /// @todo Optimize this function.
  Cell *temp = NULL;
  int x, y;

  x=0;
  y=0;

  while (!temp && x<width) {
    if (battle_map[x][y].canAttackHere() && battle_map[x][y].getCreature()->getMaster() != NULL)
      temp = &battle_map[x][y];
    else {
      y++;
      if (y == height) {
        y=0;
        x++;
      }
    }
  }

  return temp;
}

// Tells the map the mouse's position.
void Map::moveMouse(const int x, const int y, const int button) {
  int i=first_cell_coor.x, j=first_cell_coor.y;
  SDL_Rect cellPosition;

  cellPosition.x=first_cell_pos.x;
  if ( (first_cell_coor.x%2)==1 ) cellPosition.y = first_cell_pos.y+36;
  else cellPosition.y = first_cell_pos.y;

  if (mouse_over_cell)
    mouse_over_cell->removeMouse();

  // Find out which cell is the mouse over
  while (x > cellPosition.x){
    cellPosition.x += 54;
    i++;
  }
  i--;
  if (i>=first_cell_coor.x && i<horizontal_cells+first_cell_coor.x) {
    if ( (i%2)==1 ) cellPosition.y = first_cell_pos.y+36;
    else cellPosition.y = first_cell_pos.y;
    while (y > cellPosition.y){
      cellPosition.y += 72;
      j++;
    }
    j--;
    if (j>=first_cell_coor.y && j<vertical_cells+first_cell_coor.y) { // battle_map[i][j] is a valid cell and the mouse is over it
      battle_map[i][j].putMouse();
      mouse_over_cell = &battle_map[i][j];
      if (button == BUTTON_LEFT) mouseClick(i, j);
    }
  }
  // move visible map
  if ( (i<first_cell_coor.x || keys[SDLK_LEFT]) && first_cell_coor.x!=0)
    first_cell_coor.x--;
  else if ( (i>first_cell_coor.x+(horizontal_cells-1) || keys[SDLK_RIGHT]) && first_cell_coor.x!=width-horizontal_cells)
    first_cell_coor.x++;
  if ( (j<first_cell_coor.y || keys[SDLK_UP]) && first_cell_coor.y!=0)
    first_cell_coor.y--;
  else if ( (j>first_cell_coor.y+(vertical_cells-1) || keys[SDLK_DOWN]) && first_cell_coor.y!=height-vertical_cells)
    first_cell_coor.y++;
}

// Moves a creature to a cell.
void Map::moveCreature(Cell &endPosition) {
  int *path;
  int movements;
  Cell *actualPosition;
  Cell *temp;
  int actualX, actualY; // Coordinates of the actual cell
  int endX, endY; // Coordinates of the cell where to move

  actualPosition = selected_unit->getPosition();

  actualPosition->getCoordinates(actualX, actualY);
  endPosition.getCoordinates(endX, endY);

  endPosition.getPath(path, movements);
  /// @note This isn't too elegant
  for (int i=0; i<movements; i++) {
    // Make the creature face the same direction as moving
    if (path[i] == NE || path[i] == SE) selected_unit->setFacingSide(RIGHT);
    else if (path[i] == NW || path[i] == SW) selected_unit->setFacingSide(LEFT);

    selected_unit->getPosition()->setCreature(NULL);
    temp = selected_unit->getPosition()->getConnectedCell(path[i]);
    temp->setCreature(selected_unit);
    selected_unit->setPosition(*temp);
    draw();
    screen->update();
    screen->wait(100);
  }

  actualPosition->unselect(selected_unit->getMovement());
}

// Connects all the cells in the map.
void Map::connectCells(void) {
  for (int coor1=0; coor1<width; coor1++) {
    for (int coor2=0; coor2<height; coor2++) {
      if ( (coor1%2)==1 ) { // coor1 is an odd number
        if (coor1 == width-1) { // The last colum of the map
          if (coor2 == 0) {
            battle_map[coor1][coor2].connectCell(N, NULL);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2+1]);
          } else if (coor2 == height-1) {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, NULL);
            battle_map[coor1][coor2].connectCell(SW, NULL);
          } else {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2+1]);
          }
          battle_map[coor1][coor2].connectCell(NE, NULL);
          battle_map[coor1][coor2].connectCell(SE, NULL);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2]);
        } else if (coor2 == 0) { // The first row of the map
          battle_map[coor1][coor2].connectCell(N, NULL);
          battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
          battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2]);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2+1]);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2]);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2+1]);
        } else if (coor2 == height-1) { // Last row of the map
          battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
          battle_map[coor1][coor2].connectCell(S, NULL);
          battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2]);
          battle_map[coor1][coor2].connectCell(SE, NULL);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2]);
          battle_map[coor1][coor2].connectCell(SW, NULL);
        } else {
          battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
          battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
          battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2]);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2+1]);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2]);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2+1]);
        }
      } else { // coor1 is an even number
        if (coor1 == 0) { // The first colum of the map
          if (coor2 == 0) {
            battle_map[coor1][coor2].connectCell(N, NULL);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(NE, NULL);
          } else if (coor2 == height-1) {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, NULL);
            battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2-1]);
          } else {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2-1]);
          }
          battle_map[coor1][coor2].connectCell(NW, NULL);
          battle_map[coor1][coor2].connectCell(SW, NULL);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2]);
        } else if (coor1 == width-1) { // The last colum of the map
          if (coor2 == 0) {
            battle_map[coor1][coor2].connectCell(N, NULL);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(NW, NULL);
          } else if (coor2 == height-1) {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, NULL);
            battle_map[coor1][coor2].connectCell(NW,&battle_map[coor1-1][coor2-1]);
          } else {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2-1]);
          }
          battle_map[coor1][coor2].connectCell(NE, NULL);
          battle_map[coor1][coor2].connectCell(SE, NULL);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2]);
        } else if (coor2 == 0) { // The first row of the map
          battle_map[coor1][coor2].connectCell(N, NULL);
          battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
          battle_map[coor1][coor2].connectCell(NE, NULL);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2]);
          battle_map[coor1][coor2].connectCell(NW, NULL);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2]);
        } else if (coor2 == height-1) { // Last row of the map
          battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
          battle_map[coor1][coor2].connectCell(S, NULL);
          battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2-1]);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2]);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2-1]);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2]);
        } else {
          battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
          battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
          battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2-1]);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2]);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2-1]);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2]);
        }
      }
    }
  }
}

// Draws the map in the screen.
void Map::draw(void) {
  SDL_Rect position;

  // Position of the firts cell (top-left)
  position.x = first_cell_pos.x;
  if ( (first_cell_coor.x%2)==1 ) position.y = first_cell_pos.y+36;
  else position.y = first_cell_pos.y;
  position.w = 72;
  position.h = 72;

  screen->erase();
  // Draws the visible cells.
  for (int x=first_cell_coor.x; x<horizontal_cells+first_cell_coor.x; x++) {
    for (int y=first_cell_coor.y; y<vertical_cells+first_cell_coor.y; y++) {
      battle_map[x][y].draw(position);
      position.y+=72;
    }
    if ( (x%2)==1 ) position.y=first_cell_pos.y; // x is an odd number
    else position.y=first_cell_pos.y+36;
    position.x+=54;
  }
}
