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

// Starts a new animation.
void UnitAnimation::startNewAnimation(int type, Unit &unit, Cell *cell) {
  this->type = type;
  this->unit = &unit;
  initial_position = unit.getPosition();
  final_position = cell;

  frames = 0;

  cells_connected = false;
  for (int i=N; i<=NW && !cells_connected; i++)
    cells_connected |= initial_position->getConnectedCell(i) == final_position;

  if ( type == MOVE || (type == ATTACK && !unit.getProjectiles()) ) {
    state = MOVE;
    if (cell)
      cell->getPath(path, movements);
    actual_move = 0;
  } else {
    startAnimation(type);
  }

  animation_in_progress = true;
  input->setCursorType(WAIT_CURSOR);
}

// Performs all needed actions in a frame of the animation.
bool UnitAnimation::frame(void) {
  if (animation_in_progress)
    switch (state) {
      case ATTACK:
      case DIE:
        frames--;
        if (!frames) {
          initial_position->unselect();
          animation_in_progress = false;
        }
        break;
      case MOVE:
        if (actual_move >= movements) {
          initial_position->unselect();
          if (type == ATTACK) {
            startAnimation(ATTACK);
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
        // Impossible case
        break;
    }

  return !animation_in_progress;
}

// Starts a given animation.
void UnitAnimation::startAnimation(int type) {
  state = type;
  switch (type) {
    case ATTACK:
      unit->setAnimation(ATTACKING);
      final_position->getCreature()->setAnimation(DEFENDING);
      if ( unit->getProjectiles() && !cells_connected)
        final_position->getCreature()->addMagicAnimation( unit->getProjectilesType() );
      frames = unit->getNumFrames(ATTACKING);
      if (frames < final_position->getCreature()->getNumFrames(DEFENDING))
        frames = final_position->getCreature()->getNumFrames(DEFENDING);
      if (!frames) frames = 1;
      break;
    case DIE:
      unit->setAnimation(DYING);
      frames = unit->getNumFrames(DYING);
      if (!frames) frames = 1;
      break;
    default:
      // Nothing to do
      break;
  }
}
