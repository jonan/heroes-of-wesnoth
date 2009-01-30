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

#include <cstdlib>
#include <iostream>

// Sets the creature's attributes acording to his type.
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
      addAnimationImage("units/archer-idle-1", IDLE);
      addAnimationImage("units/archer-idle-2", IDLE);
      addAnimationImage("units/archer-idle-3", IDLE);
      addAnimationImage("units/archer-idle-4", IDLE);
      addAnimationImage("units/archer-idle-5", IDLE);
      addAnimationImage("units/archer-idle-6", IDLE);
      addAnimationImage("units/archer", STANDING);
      setAllAttributes(15, 3, 6, 4, 0, -1);
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
      setAllAttributes(60, 1, 25, 2, 0, -1);
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
      setAllAttributes(5, 5, 2, 6, 0, -1);
      break;
    case BLADE_MASTER:
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
      setAllAttributes(55, 2, 22, 3, 0, -1);
      break;
    case BLOOD_BAT:
      addAnimationImage("units/bloodbat-se-1", STANDING);
      addAnimationImage("units/bloodbat-se-2", STANDING);
      addAnimationImage("units/bloodbat-se-3", STANDING);
      addAnimationImage("units/bloodbat-se-4", STANDING);
      addAnimationImage("units/bloodbat-se-5", STANDING);
      addAnimationImage("units/bloodbat-se-4", STANDING);
      addAnimationImage("units/bloodbat-se-3", STANDING);
      addAnimationImage("units/bloodbat-se-2", STANDING);
      setAllAttributes(15, 5, 5, 6, 0, -1);
      break;
    case CAVE_SPIDER:
      addAnimationImage("units/cavespider-attack-melee", ATTACKING);
      addAnimationImage("units/cavespider-defend", DEFENDING);
      addAnimationImage("units/cavespider-die-1", DYING);
      addAnimationImage("units/cavespider-die-2", DYING);
      addAnimationImage("units/cavespider", STANDING);
      setAllAttributes(15, 2, 7, 2, 0, -1);
      break;
    case CHAMPION:
      addAnimationImage("units/champion-attack-1", ATTACKING);
      addAnimationImage("units/champion-attack-2", ATTACKING);
      addAnimationImage("units/champion-attack-3", ATTACKING);
      addAnimationImage("units/champion-attack-4", ATTACKING);
      addAnimationImage("units/champion-attack-5", ATTACKING);
      addAnimationImage("units/champion-attack-6", ATTACKING);
      addAnimationImage("units/champion-defend", DEFENDING);
      addAnimationImage("units/champion", STANDING);
      setAllAttributes(27, 3, 17, 3, 0, -1);
      break;
    case DEATH_BLADE:
      addAnimationImage("units/deathblade-attack1", ATTACKING);
      addAnimationImage("units/deathblade-attack2", ATTACKING);
      addAnimationImage("units/deathblade-attack3", ATTACKING);
      addAnimationImage("units/deathblade-defend-1", DEFENDING);
      addAnimationImage("units/deathblade-defend-2", DEFENDING);
      addAnimationImage("units/deathblade-dying-1", DYING);
      addAnimationImage("units/deathblade-dying-2", DYING);
      addAnimationImage("units/deathblade-dying-3", DYING);
      addAnimationImage("units/deathblade-dying-4", DYING);
      addAnimationImage("units/deathblade-dying-5", DYING);
      addAnimationImage("units/deathblade-dying-6", DYING);
      addAnimationImage("units/deathblade-dying-7", DYING);
      addAnimationImage("units/deathblade", STANDING);
      setAllAttributes(35, 2, 18, 3, 0, -1);
      break;
    case FIGHTER:
      addAnimationImage("units/fighter-melee-1", ATTACKING);
      addAnimationImage("units/fighter-melee-2", ATTACKING);
      addAnimationImage("units/fighter-defend", DEFENDING);
      addAnimationImage("units/fighter-idle-1", IDLE);
      addAnimationImage("units/fighter-idle-2", IDLE);
      addAnimationImage("units/fighter-idle-3", IDLE);
      addAnimationImage("units/fighter-idle-4", IDLE);
      addAnimationImage("units/fighter-idle-5", IDLE);
      addAnimationImage("units/fighter-idle-6", IDLE);
      addAnimationImage("units/fighter-idle-7", IDLE);
      addAnimationImage("units/fighter-idle-8", IDLE);
      addAnimationImage("units/fighter-idle-9", IDLE);
      addAnimationImage("units/fighter-idle-10", IDLE);
      addAnimationImage("units/fighter-idle-11", IDLE);
      addAnimationImage("units/fighter-idle-12", IDLE);
      addAnimationImage("units/fighter", STANDING);
      setAllAttributes(20, 3, 10, 3, 0, -1);
      break;
    case FLANKER:
      addAnimationImage("units/flanker-attack1", ATTACKING);
      addAnimationImage("units/flanker-attack2", ATTACKING);
      addAnimationImage("units/flanker-defend", DEFENDING);
      addAnimationImage("units/flanker", STANDING);
      setAllAttributes(8, 2, 6, 5, 0, -1);
      break;
    case PILLAGER:
      addAnimationImage("units/pillager-attack2", ATTACKING);
      addAnimationImage("units/pillager-attack", ATTACKING);
      addAnimationImage("units/pillager-defend", DEFENDING);
      addAnimationImage("units/pillager", STANDING);
      setAllAttributes(17, 4, 8, 4, 0, -1);
      break;
    case RANGER:
      addAnimationImage("units/ranger-sword-1", ATTACKING);
      addAnimationImage("units/ranger-sword-2", ATTACKING);
      addAnimationImage("units/ranger-sword-3", ATTACKING);
      addAnimationImage("units/ranger-bow-defend", DEFENDING);
      addAnimationImage("units/ranger-die1", DYING);
      addAnimationImage("units/ranger-die2", DYING);
      addAnimationImage("units/ranger-die3", DYING);
      addAnimationImage("units/ranger-die4", DYING);
      addAnimationImage("units/ranger", STANDING);
      setAllAttributes(35, 3, 15, 2, 0, -1);
      break;
    case SERGEANT:
      addAnimationImage("units/sergeant-attack-sword-1", ATTACKING);
      addAnimationImage("units/sergeant-attack-sword-2", ATTACKING);
      addAnimationImage("units/sergeant-attack-sword-3", ATTACKING);
      addAnimationImage("units/sergeant-defend", DEFENDING);
      addAnimationImage("units/sergeant", STANDING);
      setAllAttributes(20, 3, 10, 3, 0, -1);
      break;
    case SHYDE:
      addAnimationImage("units/shyde-ftouch-attack1", ATTACKING);
      addAnimationImage("units/shyde-ftouch-attack2", ATTACKING);
      addAnimationImage("units/shyde-ftouch-attack3", ATTACKING);
      addAnimationImage("units/shyde-defend", DEFENDING);
      addAnimationImage("units/shyde", STANDING);
      setAllAttributes(10, 4, 17, 4, 10, WHITE_MISSILE);
      break;
    case SKELETON:
      addAnimationImage("units/skeleton-attack-1", ATTACKING);
      addAnimationImage("units/skeleton-attack-2", ATTACKING);
      addAnimationImage("units/skeleton-attack-3", ATTACKING);
      addAnimationImage("units/skeleton-attack-4", ATTACKING);
      addAnimationImage("units/skeleton-attack-5", ATTACKING);
      addAnimationImage("units/skeleton-defend-1", DEFENDING);
      addAnimationImage("units/skeleton-defend-2", DEFENDING);
      addAnimationImage("units/skeleton-dying-1", DYING);
      addAnimationImage("units/skeleton-dying-2", DYING);
      addAnimationImage("units/skeleton-dying-3", DYING);
      addAnimationImage("units/skeleton-dying-4", DYING);
      addAnimationImage("units/skeleton-dying-5", DYING);
      addAnimationImage("units/skeleton-dying-6", DYING);
      addAnimationImage("units/skeleton-dying-7", DYING);
      addAnimationImage("units/skeleton-idle-1", IDLE);
      addAnimationImage("units/skeleton-idle-2", IDLE);
      addAnimationImage("units/skeleton-idle-3", IDLE);
      addAnimationImage("units/skeleton", STANDING);
      setAllAttributes(20, 3, 10, 3, 0, -1);
      break;
    case WOLF_RIDER:
      addAnimationImage("units/wolf-rider-attack", ATTACKING);
      addAnimationImage("units/wolf-rider-defend", DEFENDING);
      addAnimationImage("units/wolf-rider", STANDING);
      setAllAttributes(22, 4, 12, 4, 0, -1);
      break;
    default:
      std::cout << "\n\tWrong unit type : " << type << "\n\n";
      exit(EXIT_FAILURE);
  }
}
