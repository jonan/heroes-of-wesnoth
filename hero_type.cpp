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

#include "hero.hpp"

// Sets the heros attributes acording to his type.
void Hero::setCreaturesAttributes(void) {
  switch (type) {
    case FIGHTER:
      addAnimationImage("units/grand-knight-attack-sword", ATTACKING);
      addAnimationImage("units/grand-knight-defend", DEFENDING);
      addAnimationImage("units/grand-knight", STANDING);
      setAllAttributes(3, 0, 45, 30, 5, 5);
    /// @todo Add more types of heroes
  }
}
