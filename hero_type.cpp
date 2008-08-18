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

#include "hero.hpp"

#include <cstdlib>
#include <iostream>

// Sets the hero's attributes acording to his type.
void Hero::setCreaturesAttributes(void) {
  switch (type) {
    case ELF:
      addAnimationImage("units/outrider-melee-1", ATTACKING);
      addAnimationImage("units/outrider-melee-2", ATTACKING);
      addAnimationImage("units/outrider-defend", DEFENDING);
      addAnimationImage("units/outrider", STANDING);
      setAllAttributes(300, 5, 45, 5, 0, -1);
      break;
    case HUMAN:
      addAnimationImage("units/grand-knight-attack-sword", ATTACKING);
      addAnimationImage("units/grand-knight-defend", DEFENDING);
      addAnimationImage("units/grand-knight", STANDING);
      setAllAttributes(300, 5, 45, 5, 0, -1);
      break;
    case UNDEAD:
      addAnimationImage("units/soulless-mounted-attack", ATTACKING);
      addAnimationImage("units/soulless-mounted-defend", DEFENDING);
      addAnimationImage("units/soulless-mounted-die-1", DYING);
      addAnimationImage("units/soulless-mounted-die-2", DYING);
      addAnimationImage("units/soulless-mounted-die-3", DYING);
      addAnimationImage("units/soulless-mounted-die-4", DYING);
      addAnimationImage("units/soulless-mounted", STANDING);
      setAllAttributes(300, 5, 45, 5, 0, -1);
      break;
    default:
      std::cout << "\n\tWrong hero type : " << type << "\n\n";
      exit(EXIT_FAILURE);
  }
}
