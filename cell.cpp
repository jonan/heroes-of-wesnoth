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

#include "cell.hpp"

#include "graphics.hpp"
#include "unit.hpp"

using video_engine::screen;

// Constructor
Cell::Cell(void) {
  special_terrain = NULL;
  item = '-';
  creature = NULL;
  path = NULL;
  map_position.x = map_position.y = -1;

  for (int i=N; i<=NW; i++)
    connected_cell[i] = NULL;

  mouse_over = false;
  selected = false;
  can_move = false;
  can_attack = false;
  visible = false;
}

// Destructor
Cell::~Cell(void) {
  if (path) delete [] path;
  if (special_terrain) delete special_terrain;
}

// Adds an image to the cell's terrain.
void Cell::addImage(SDL_Surface &terrain, const char type) {
  if (type != -1) {
    // If a new type is assigned, it means the new surface is
    // the main one, so all previous ones need to be deleted.
    this->terrain.clear();
    // Erase special image only if it's not an item
    if (special_terrain && item == '-') {
      delete special_terrain;
      special_terrain = NULL;
    }
    this->type = type;
  }
  this->terrain.push_back(&terrain);
}

// Adds a special image to the cell's terrain.
void Cell::addSpecialImage(SDL_Surface &terrain) {
  if (!special_terrain) {
    special_terrain = new SpecialImage;
    special_terrain->position.x = -(terrain.w-72)/2;
    special_terrain->position.y = -(terrain.h-72)/2;
    special_terrain->sprite = 0;
  }
  special_terrain->image_list.push_back(&terrain);
}

// Puts a creature in the cell.
void Cell::setCreature(Unit *creature) {
  this->creature = creature;
  if (creature) creature->setPosition(*this);
}

// Puts an item on the cell.
void Cell::setItem(char type) {
  if (special_terrain) {
    delete special_terrain;
    special_terrain = NULL;
  }
  item = type;
}

// Sets the cells map coordinates.
void Cell::setCoordinates(const int x, const int y) {
  map_position.x = x;
  map_position.y = y;
}

// Returns the cells map coordinates.
void Cell::getCoordinates(int &x, int &y) {
  x = map_position.x;
  y = map_position.y;
}

// Returns the path that the unit has to follow to
// reach this cell and how many movements are needed.
void Cell::getPath(int* &path, int &movements) {
  path = this->path;
  movements = this->movements;
}

// The cell is selected and the cell where
// the unit can move are marked.
void Cell::select(void) {
  if (creature!=NULL) {
    selected = true;
    creatureMovement(creature->getMovement(), NULL, 0);
  }
}

// Marks the cell as not being selected and tells all the cells
// where the unit could move that now it can not move there.
void Cell::unselect(void) {
  selected = false;
  eraseMovement();
}

// Calculates which cells are visible.
void Cell::calculateView(int visibility) {
  if (visibility > 0) {
    visible = true;
    for (int i=N; i<=NW; i++) { // The six relative positions to the cell.
      if (connected_cell[i])
        connected_cell[i]->calculateView(visibility-1);
    }
  }
}

// Indicates which are the cells next to this one
// in any direction (N, NE, SE, S, SW or NW).
void Cell::connectCell(const int position, Cell* connected_cell){
  this->connected_cell[position] = connected_cell;
}

// Draws the cell in the screen.
void Cell::draw(SDL_Rect position, const int part) {
  // Cells can be drawn in negative positions, so original
  // coordinates need to be saved (SDL will change them).
  int x = position.x;
  int y = position.y;
  if (visible) {
    if (part == TERRAIN) {
      for (unsigned int i=0; i<terrain.size(); i++) {
        screen->draw(terrain[i], position);
        position.x = x;
        position.y = y;
      }
    } else if (part == SPECIAL) {
      if (special_terrain) {
        position.x += special_terrain->position.x;
        position.y += special_terrain->position.y;
        screen->draw(special_terrain->image_list[special_terrain->sprite/NUM_FRAMES_FOR_SPRITE], position);
        position.x = x;
        position.y = y;
        special_terrain->sprite++;
        if (special_terrain->sprite/NUM_FRAMES_FOR_SPRITE == special_terrain->image_list.size())
          special_terrain->sprite = 0;
      }
    } else if (part == UNIT) {
      if (mouse_over) {
        screen->draw(alpha, position);
        position.x = x;
        position.y = y;
      }
      if (can_move) {
        screen->draw(alpha, position);
        position.x = x;
        position.y = y;
      }
      if (creature) {
        creature->draw(position);
        position.x = x;
        position.y = y;
      }
      if (selected) {
        screen->draw(alpha, position);
        position.x = x;
        position.y = y;
      }
    }
  } else {
      screen->draw(stars, position);
      position.x = x;
      position.y = y;
    }
}

// Calculates to what cells can a creature move.
void Cell::creatureMovement(const int movement, int *path, const int movements) {
  if (movement_penalty != 1000) { // A creature can move here
    if (path == NULL) { // It's the first call to this funtion so the creature is over this cell.
      for (int i=N; i<=NW; i++) {
        if (connected_cell[i]) {
          int *temp_path = new int[1];
          temp_path[0] = i;
          connected_cell[i]->creatureMovement(movement, temp_path, 1);
        }
      }
    } else if (creature) {
      if (this->path == NULL || this->movements > movements-1) {
        can_attack = true;
        if (this->path != NULL) delete [] this->path;
        this->movements = movements-1;
        this->path = new int[this->movements];
        for (int i=0; i<(this->movements); i++)
          this->path[i] = path[i];
        delete [] path;
      }
    } else if (movement>0) {
      if (this->path == NULL || this->movements > movements) { // Need to change path
        can_move = true;
        if (this->path != NULL) delete [] this->path;
        this->path = path;
        this->movements = movements;
        for (int i=N; i<=NW; i++) {
          if (connected_cell[i]) {
            int *temp_path = new int[this->movements+1];
            for (int j=0; j<(this->movements); j++)
              temp_path[j] = this->path[j];
            temp_path[this->movements] = i;
            connected_cell[i]->creatureMovement(movement-movement_penalty, temp_path, movements+1);
          }
        }
      }
    } else delete [] path;
  } else delete [] path;
}

// Erases previos calculations about a creatures movement.
void Cell::eraseMovement(void) {
  if (can_move || can_attack) {
    can_move = false;
    can_attack = false;
    delete [] path;
    path = NULL;
    movements = 0;
    for (int i=N; i<=NW; i++) {
      if (connected_cell[i])
        connected_cell[i]->eraseMovement();
    }
  }
}
