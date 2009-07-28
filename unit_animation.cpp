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

// Constructor
UnitAnimation::UnitAnimation(Unit &unit, Cell &cell, int type) {
  this->type = type;
  this->unit = &unit;
  initial_position = unit.getPosition();
  this->final_position = &cell;
  cell.getPath(path, movements);
  ended = false;
  frames = 0;
  input->setCursorType(WAIT_CURSOR);
}

// 
void UnitAnimation::frame(void) {
  if (!ended) {
    static int temp = 0;

    if (temp >= movements) {
      ended = true;
      temp = 0;
      initial_position->unselect();
      input->setCursorType(NORMAL_CURSOR);
    } else {
      if (!(frames%FRAMES_PER_MOVE)) {
        // Make the unit face the same direction as moving
        if (path[temp] == NE || path[temp] == SE)
          unit->setFacingSide(FACE_RIGHT);
        else if (path[temp] == NW || path[temp] == SW)
          unit->setFacingSide(FACE_LEFT);

        unit->getPosition()->setCreature(NULL);
        unit->getPosition()->getConnectedCell(path[temp])->setCreature(unit);
        temp++;
      }
      frames++;
    }
  }
}
