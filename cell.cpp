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

#include "cell.hpp"

#include "graphics.hpp"
#include "structs.hpp"
#include "unit.hpp"

using video_engine::screen;

// Constructor
Cell::Cell(void) {
  special_images = NULL;

  creature = NULL;
  item = '-';

  path = NULL;

  for (int i=N; i<=NW; i++)
    connected_cell[i] = NULL;
  map_position = NULL;

  mouse_over = false;
  selected = false;

  can_move = false;
  can_attack = false;

  visible = false;
}

// Destructor
Cell::~Cell(void) {
  delete map_position;
  delete [] path;
  delete special_images;
}

// Adds an image to the cell's terrain.
void Cell::addImage(SDL_Surface &terrain, const char type) {
  if (type != -1) {
    // If a new type is assigned, it means the new surface is
    // the main one, so all previous ones need to be deleted.
    terrain_images.clear();
    // Erase special image only if it's not an item
    if (special_images && item == '-') {
      delete special_images;
      special_images = NULL;
    }
    this->type = type;
  }
  terrain_images.push_back(&terrain);
}

// Adds a special image to the cell's terrain.
void Cell::addSpecialImage(SDL_Surface &terrain) {
  if (!special_images) {
    special_images = new SpecialImage;
    special_images->position.x = -(terrain.w-72)/2;
    special_images->position.y = -(terrain.h-72)/2;
    special_images->sprite = 0;
  }
  special_images->image_list.push_back(&terrain);
}

// Puts a creature in the cell.
void Cell::setCreature(Unit *creature) {
  this->creature = creature;
  if (creature) creature->setPosition(*this);
}

// Puts an item on the cell.
void Cell::setItemType(char type) {
  if (special_images) {
    delete special_images;
    special_images = NULL;
  }
  item = type;
}

// Sets the cells map coordinates.
void Cell::setCoordinates(const int x, const int y) {
  if (!map_position) {
    map_position = new Coordinates;
    map_position->x = x;
    map_position->y = y;
  }
}

// Returns the cells map coordinates.
void Cell::getCoordinates(int &x, int &y) {
  if (map_position) {
    x = map_position->x;
    y = map_position->y;
  } else {
    x = y = -1;
  }
}

// Returns the path that the unit has to follow to
// reach this cell and how many movements are needed.
void Cell::getPath(int* &path, int &movements) {
  path = this->path;
  movements = this->movements;
}

// The cell is selected and the cells where
// the unit can move are marked.
void Cell::select(void) {
  if (creature!=NULL) {
    selected = true;
    calculateMovement(creature->getMovement(), NULL, 0);
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
void Cell::connectCell(const int position, Cell* connected_cell) {
  this->connected_cell[position] = connected_cell;
}

// Draws the cell in the screen.
void Cell::draw(SDL_Rect position, const int part) {
  // Cells can be drawn in negative positions, so original
  // coordinates need to be saved (SDL will change them).
  int x = position.x;
  int y = position.y;
  if (visible) {
    switch (part) {
      case TERRAIN:
        for (unsigned int i=0; i<terrain_images.size(); i++) {
          screen->draw(terrain_images[i], position);
          position.x = x;
          position.y = y;
        }
        break;
      case SPECIAL:
        if (special_images) {
          position.x += special_images->position.x;
          position.y += special_images->position.y;
          screen->draw(special_images->image_list[special_images->sprite/NUM_FRAMES_FOR_SPRITE], position);
          position.x = x;
          position.y = y;
          special_images->sprite++;
          if (special_images->sprite/NUM_FRAMES_FOR_SPRITE == special_images->image_list.size())
            special_images->sprite = 0;
        }
        break;
      case UNIT:
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
        break;
      default:
        // Impossible case
        break;
    }
  } else {
    screen->draw(stars, position);
    position.x = x;
    position.y = y;
  }
}

// Calculates to what cells can a creature move.
void Cell::calculateMovement(const int creature_movement, int *path, const int movements) {
  if (passable) { // A creature can move here
    if (path == NULL) { // It's the first call to this funtion so the creature is over this cell.
      can_attack = true;
      for (int i=N; i<=NW; i++) {
        if (connected_cell[i]) {
          int *temp_path = new int[1];
          temp_path[0] = i;
          connected_cell[i]->calculateMovement(creature_movement, temp_path, 1);
        }
      }
    } else if (creature) { // If there's a creature, move to the cell next to it to attack.
      if (this->path == NULL || this->movements > movements-1) {
        can_attack = true;
        delete [] this->path;
        this->movements = movements-1;
        this->path = new int[this->movements];
        for (int i=0; i<(this->movements); i++)
          this->path[i] = path[i];
        delete [] path;
      } else delete [] path;
    } else if (creature_movement>0) {
      if (this->path == NULL || this->movements > movements) {
        can_move = true;
        delete [] this->path;
        this->path = path;
        this->movements = movements;
        for (int i=N; i<=NW; i++) {
          if (connected_cell[i]) {
            int *temp_path = new int[this->movements+1];
            for (int j=0; j<(this->movements); j++)
              temp_path[j] = this->path[j];
            temp_path[this->movements] = i;
            connected_cell[i]->calculateMovement(creature_movement-1, temp_path, movements+1);
          }
        }
      } else delete [] path;
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
