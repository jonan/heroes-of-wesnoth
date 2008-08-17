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

#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "timer.hpp"
#include "unit.hpp"

// events_engine
using events_engine::input;
using events_engine::keys;
using events_engine::BUTTON_LEFT;
using events_engine::BUTTON_RIGHT;
using events_engine::NORMAL;
using events_engine::ATTACK;
using events_engine::MOVE;
// video_engine
using video_engine::screen;

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
  // Calculate the size of the map's window
  screen->getScreenSize(window_width, window_height);
  horizontal_cells = (window_width/108)*2+2; // +2 cells that don't fit compleatly
  vertical_cells = (window_height/72)+2; // +2 cells that don't fit compleatly
  if (horizontal_cells > width) horizontal_cells = width;
  if (vertical_cells > height) vertical_cells = height;
  // Adjust the first cell's coordinates
  first_cell_pos.x = -53;
  first_cell_pos.y = -72;

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
    if (battle_map[x][y].canAttackHere() &&
        battle_map[x][y].getCreature()->getMaster() != selected_unit->getMaster()) {
      temp = &battle_map[x][y];
    } else {
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
  if ( (first_cell_coor.x%2)==1 )
    cellPosition.y = first_cell_pos.y+36;
  else
    cellPosition.y = first_cell_pos.y;

  if (mouse_over_cell)
    mouse_over_cell->removeMouse();

  // Find out which cell is the mouse over
  while (x > cellPosition.x){
    cellPosition.x += 54;
    i++;
  }
  i--;
  if ( (i%2)==1 )
    cellPosition.y = first_cell_pos.y+36;
  else
    cellPosition.y = first_cell_pos.y;
  while (y > cellPosition.y){
    cellPosition.y += 72;
    j++;
  }
  j--;
  if (i>0 && i<width && j>0 && j<height) {
    // battle_map[i][j] is a valid cell and the mouse is over it
    if (i!=0 && i!=width-1 && j!=0 && j!=height-1) { // Cell is not in one of the map's borders
      battle_map[i][j].putMouse();
      mouse_over_cell = &battle_map[i][j];
      mouseOverCell(i, j);
      if (button == BUTTON_LEFT) mouseLeftClick(i, j);
      if (button == BUTTON_RIGHT) mouseRightClick(i, j);
    }
  }

  // move visible map
  if ( (x==0 || keys[SDLK_LEFT]) && first_cell_coor.x!=0)
    first_cell_coor.x--;
  else if ( (x==window_width-1 || keys[SDLK_RIGHT]) && first_cell_coor.x!=width-horizontal_cells)
    first_cell_coor.x++;
  if ( (y==0 || keys[SDLK_UP]) && first_cell_coor.y!=0)
    first_cell_coor.y--;
  else if ( (y==window_height-1 || keys[SDLK_DOWN]) && first_cell_coor.y!=height-vertical_cells)
    first_cell_coor.y++;
}

// Function to execute when the mouse is over a cell.
void Map::mouseOverCell(const int x, const int y) {
  if (battle_map[x][y].canAttackHere() && selected_unit->getPosition() != &battle_map[x][y])
    input->setCursorType(ATTACK);
  else if (battle_map[x][y].canMoveHere())
    input->setCursorType(MOVE);
  else
    input->setCursorType(NORMAL);
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool Map::frame(void) {
  /* This function just does the necessary operations any type of map
     will need every frame, but every inhereted class will need to re-implement
     it and (probably) call Map::frame().
     The return value is not important, so it's set to false. */

  // Calculate the size of the map's window (might have changed)
  int new_width, new_height;
  bool changed = false; // To check if the window size changed
  screen->getScreenSize(new_width, new_height);
  if (new_width != window_width) {
    changed = true;
    window_width = new_width;
    horizontal_cells = (window_width/108)*2+2; // +2 cells that don't fit compleatly
    if (horizontal_cells > width) horizontal_cells = width;
  }
  if (new_height != window_height) {
    changed = true;
    window_height = new_height;
    vertical_cells = (window_height/72)+2; // +2 cells that don't fit compleatly
    if (vertical_cells > height) vertical_cells = height;
  }
  // If the window size has change, center the view
  if (changed && selected_unit) centerView(*selected_unit);

  return false;
}

// Moves a creature to a cell.
void Map::moveCreature(Cell &end_position) {
  int *path;
  int movements;
  Cell *temp;

  Cell* actual_position = selected_unit->getPosition();
  end_position.getPath(path, movements);

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

  actual_position->unselect();
}

// Connects all the cells in the map.
void Map::connectCells(void) {
  for (int coor1=0; coor1<width; coor1++) {
    for (int coor2=0; coor2<height; coor2++) {
      if ( (coor1%2)==1 ) { // coor1 is an odd number
        if (coor1 == width-1) { // The last colum of the map
          if (coor2 == 0) {
            // battle_map[coor1][coor2].connectCell(N, NULL);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2+1]);
          } else if (coor2 == height-1) {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            // battle_map[coor1][coor2].connectCell(S, NULL);
            // battle_map[coor1][coor2].connectCell(SW, NULL);
          } else {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2+1]);
          }
          // battle_map[coor1][coor2].connectCell(NE, NULL);
          // battle_map[coor1][coor2].connectCell(SE, NULL);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2]);
        } else if (coor2 == 0) { // The first row of the map
          // battle_map[coor1][coor2].connectCell(N, NULL);
          battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
          battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2]);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2+1]);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2]);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2+1]);
        } else if (coor2 == height-1) { // Last row of the map
          battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
          // battle_map[coor1][coor2].connectCell(S, NULL);
          battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2]);
          // battle_map[coor1][coor2].connectCell(SE, NULL);
          battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2]);
          // battle_map[coor1][coor2].connectCell(SW, NULL);
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
            // battle_map[coor1][coor2].connectCell(N, NULL);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            // battle_map[coor1][coor2].connectCell(NE, NULL);
          } else if (coor2 == height-1) {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            // battle_map[coor1][coor2].connectCell(S, NULL);
            battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2-1]);
          } else {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(NE, &battle_map[coor1+1][coor2-1]);
          }
          // battle_map[coor1][coor2].connectCell(NW, NULL);
          // battle_map[coor1][coor2].connectCell(SW, NULL);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2]);
        } else if (coor1 == width-1) { // The last colum of the map
          if (coor2 == 0) {
            // battle_map[coor1][coor2].connectCell(N, NULL);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            // battle_map[coor1][coor2].connectCell(NW, NULL);
          } else if (coor2 == height-1) {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            // battle_map[coor1][coor2].connectCell(S, NULL);
            battle_map[coor1][coor2].connectCell(NW,&battle_map[coor1-1][coor2-1]);
          } else {
            battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
            battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
            battle_map[coor1][coor2].connectCell(NW, &battle_map[coor1-1][coor2-1]);
          }
          // battle_map[coor1][coor2].connectCell(NE, NULL);
          // battle_map[coor1][coor2].connectCell(SE, NULL);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2]);
        } else if (coor2 == 0) { // The first row of the map
          //  battle_map[coor1][coor2].connectCell(N, NULL);
          battle_map[coor1][coor2].connectCell(S, &battle_map[coor1][coor2+1]);
          // battle_map[coor1][coor2].connectCell(NE, NULL);
          battle_map[coor1][coor2].connectCell(SE, &battle_map[coor1+1][coor2]);
          // battle_map[coor1][coor2].connectCell(NW, NULL);
          battle_map[coor1][coor2].connectCell(SW, &battle_map[coor1-1][coor2]);
        } else if (coor2 == height-1) { // Last row of the map
          battle_map[coor1][coor2].connectCell(N, &battle_map[coor1][coor2-1]);
          // battle_map[coor1][coor2].connectCell(S, NULL);
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

  screen->erase();
  // Draws the visible cells.
  for (int i=TERRAIN; i<=UNIT; i++) {
    // Position of the firts cell (top-left)
    position.x = first_cell_pos.x;
    if ( (first_cell_coor.x%2)==1 )
      position.y = first_cell_pos.y+36;
    else
      position.y = first_cell_pos.y;
    position.w = 72;
    position.h = 72;
    // Draw
    for (int x=first_cell_coor.x; position.x<window_width && x<width; x++) {
      for (int y=first_cell_coor.y; position.y<window_height && y<height; y++) {
        battle_map[x][y].draw(position, i);
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

// Centers the map view in a given creature
void Map::centerView(Unit& creature) {
  int x, y;
  creature.getPosition()->getCoordinates(x, y);

  x -= horizontal_cells/2;
  y -= vertical_cells/2;
  if (x<0) x=0;
  if (y<0) y=0;
  if (width-x < horizontal_cells) x -= horizontal_cells-(width-x);
  if (height-y < vertical_cells) y -= vertical_cells-(height-y);

  first_cell_coor.x = x;
  first_cell_coor.y = y;
}
