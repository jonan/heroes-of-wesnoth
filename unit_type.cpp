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

#include "unit.hpp"

// Sets the creatures attributes acording to his type.
void Unit::setCreaturesAttributes(void) {
  switch (type) {
    case ARCHER:
      addAnimationImage("units/archer-sword-1", ATTACKING);
      addAnimationImage("units/archer-sword-2", ATTACKING);
      addAnimationImage("units/archer-sword-3", ATTACKING);
      addAnimationImage("units/archer-sword-4", ATTACKING);
      addAnimationImage("units/archer-bow-defend", DEFENDING);
      addAnimationImage("units/archer-die1", DYING);
      addAnimationImage("units/archer-die2", DYING);
      addAnimationImage("units/archer-die3", DYING);
      addAnimationImage("units/archer-die4", DYING);
      addAnimationImage("units/archer", STANDING);
      setAllAttributes(15, 10, 25, 3, 2, 2);
      break;
    case ARMAGEDDON:
      addAnimationImage("units/armageddon-attack-melee1", ATTACKING);
      addAnimationImage("units/armageddon-attack-melee2", ATTACKING);
      addAnimationImage("units/armageddon-attack-melee3", ATTACKING);
      addAnimationImage("units/armageddon-defend", DEFENDING);
      addAnimationImage("units/armageddon-die1", DYING);
      addAnimationImage("units/armageddon-die2", DYING);
      addAnimationImage("units/armageddon-die3", DYING);
      addAnimationImage("units/armageddon-die4", DYING);
      addAnimationImage("units/armageddon-die5", DYING);
      addAnimationImage("units/armageddon-die6", DYING);
      addAnimationImage("units/armageddon", STANDING);
      setAllAttributes(65, 0, 25, 10, 2, 2);
      break;
    case BAT:
      addAnimationImage("units/bat-se-1", STANDING);
      addAnimationImage("units/bat-se-2", STANDING);
      addAnimationImage("units/bat-se-3", STANDING);
      addAnimationImage("units/bat-se-4", STANDING);
      addAnimationImage("units/bat-se-5", STANDING);
      addAnimationImage("units/bat-se-4", STANDING);
      addAnimationImage("units/bat-se-3", STANDING);
      addAnimationImage("units/bat-se-2", STANDING);
      setAllAttributes(25, 0, 5, 3, 4, 4);
      break;
    case BLADEMASTER:
      addAnimationImage("units/blademaster-attack-close1", ATTACKING);
      addAnimationImage("units/blademaster-attack-close2", ATTACKING);
      addAnimationImage("units/blademaster-defend", DEFENDING);
      addAnimationImage("units/blademaster-die-1", DYING);
      addAnimationImage("units/blademaster-die-2", DYING);
      addAnimationImage("units/blademaster-die-3", DYING);
      addAnimationImage("units/blademaster-die-4", DYING);
      addAnimationImage("units/blademaster-die-5", DYING);
      addAnimationImage("units/blademaster-die-6", DYING);
      addAnimationImage("units/blademaster-die-7", DYING);
      addAnimationImage("units/blademaster", STANDING);
      setAllAttributes(45, 0, 20, 7, 4, 3);
      break;
    case CAVESPIDER:
      addAnimationImage("units/cavespider-attack-melee", ATTACKING);
      addAnimationImage("units/cavespider-defend", DEFENDING);
      addAnimationImage("units/cavespider-die-1", DYING);
      addAnimationImage("units/cavespider-die-2", DYING);
      addAnimationImage("units/cavespider", STANDING);
      setAllAttributes(35, 0, 10, 4, 3, 1);
      break;
    case FLANKER:
      addAnimationImage("units/flanker-attack1", ATTACKING);
      addAnimationImage("units/flanker-attack2", ATTACKING);
      addAnimationImage("units/flanker-defend", DEFENDING);
      addAnimationImage("units/flanker", STANDING);
      setAllAttributes(10, 0, 7, 2, 5, 3);
      break;
    case PILLAGER:
      addAnimationImage("units/pillager-attack2", ATTACKING);
      addAnimationImage("units/pillager-attack", ATTACKING);
      addAnimationImage("units/pillager-defend", DEFENDING);
      addAnimationImage("units/pillager", STANDING);
      setAllAttributes(40, 0, 18, 6, 3, 5);
      break;
    case SERGEANT:
      addAnimationImage("units/sergeant-attack-sword-1", ATTACKING);
      addAnimationImage("units/sergeant-attack-sword-2", ATTACKING);
      addAnimationImage("units/sergeant-attack-sword-3", ATTACKING);
      addAnimationImage("units/sergeant-defend", DEFENDING);
      addAnimationImage("units/sergeant", STANDING);
      setAllAttributes(50, 0, 17, 10, 2, 3);
      break;
    case SKELETON:
      addAnimationImage("units/skeleton-attack", ATTACKING);
      addAnimationImage("units/skeleton-attackb", ATTACKING);
      addAnimationImage("units/skeleton-defend", DEFENDING);
      addAnimationImage("units/skeleton-dying-1", DYING);
      addAnimationImage("units/skeleton-dying-2", DYING);
      addAnimationImage("units/skeleton-dying-3", DYING);
      addAnimationImage("units/skeleton-dying-4", DYING);
      addAnimationImage("units/skeleton-dying-5", DYING);
      addAnimationImage("units/skeleton-dying-6", DYING);
      addAnimationImage("units/skeleton-dying-7", DYING);
      addAnimationImage("units/skeleton", STANDING);
      setAllAttributes(35, 0, 15, 8, 2, 2);
      break;
    case WOLF_RIDER:
      addAnimationImage("units/wolf-rider-attack", ATTACKING);
      addAnimationImage("units/wolf-rider-defend", DEFENDING);
      addAnimationImage("units/wolf-rider", STANDING);
      setAllAttributes(28, 0, 13, 7, 5, 4);
  }
}
