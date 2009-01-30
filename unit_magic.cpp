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

#include "unit.hpp"

#include "graphics.hpp"

// video_engine
using video_engine::screen;
using video_engine::OPAQUE;
using video_engine::NONE;

// Adds a magic animation.
void Unit::addMagicAnimation(const int spell) {
  magic_spell = new SpecialImage;
  magic_spell->sprite = 0;
  magic_spell->position.x = 0;
  magic_spell->position.y = 0;

  // Set the varibles depending of the tipe of item.
  switch (spell) {
    case WHITE_MISSILE:
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-1", OPAQUE, NONE, 0));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-2", OPAQUE, NONE, 0));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-3", OPAQUE, NONE, 0));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-4", OPAQUE, NONE, 0));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-5", OPAQUE, NONE, 0));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-6", OPAQUE, NONE, 0));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-7", OPAQUE, NONE, 0));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-8", OPAQUE, NONE, 0));
      break;
    default: {} // Imposible case
  }

  magic_spell->position.x = -(magic_spell->image_list[0]->w-72)/2;
  magic_spell->position.y = -(magic_spell->image_list[0]->h-72)/2;
}
