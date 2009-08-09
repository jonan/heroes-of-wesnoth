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

#include "unit_animation.hpp"

#include "events.hpp"
#include "cell.hpp"
#include "unit.hpp"

// events_engine
using events_engine::input;
using events_engine::NORMAL_CURSOR;
using events_engine::WAIT_CURSOR;
// video_engine
using video_engine::FACE_RIGHT;
using video_engine::FACE_LEFT;

// 
void UnitAnimation::startNewAnimation(int type, Unit &unit, Cell *cell) {
  this->type = type;
  this->unit = &unit;
  initial_position = unit.getPosition();
  final_position = cell;

  /*bool cells_connected = false;
  for (int i=N; i<=NW; i++)
    cells_connected |= initial_position->getConnectedCell(i) == final_position;*/

  if ( type == MOVE || (type == ATTACK && !unit.getProjectiles()) ) {
    state = MOVE;
    if (cell)
      cell->getPath(path, movements);
    actual_move = 0;
  } else {
    state = type;
  }

  frames = 0;
  animation_in_progress = true;
  input->setCursorType(WAIT_CURSOR);
}

// 
bool UnitAnimation::frame(void) {
  if (animation_in_progress)
    switch (state) {
      case ATTACK:
        animation_in_progress = false;
        break;
      case DIE:
        animation_in_progress = false;
        break;
      case MOVE:
        if (actual_move >= movements) {
          initial_position->unselect();
          if (type == ATTACK) {
            state = ATTACK;
          } else {
            animation_in_progress = false;
            input->setCursorType(NORMAL_CURSOR);
          }
        } else {
          if (!(frames%FRAMES_PER_MOVE)) {
            // Make the unit face the same direction as moving
            if (path[actual_move] == NE || path[actual_move] == SE)
              unit->setFacingSide(FACE_RIGHT);
            else if (path[actual_move] == NW || path[actual_move] == SW)
              unit->setFacingSide(FACE_LEFT);

            unit->getPosition()->setCreature(NULL);
            unit->getPosition()->getConnectedCell(path[actual_move])->setCreature(unit);
            actual_move++;
          }
          frames++;
        }
        break;
      default:
        // Nothing to do
        break;
    }

  return !animation_in_progress;
}
