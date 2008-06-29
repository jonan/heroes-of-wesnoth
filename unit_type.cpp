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
void unit::setCreaturesAttributes(void) {
   if (type == ARCHER) {
      addStandingImage("units/archer");
      setAllAttributes(15, 0, 25, 3, 2, 2);
      addDyingImage("units/archer-die1");
      addDyingImage("units/archer-die2");
      addDyingImage("units/archer-die3");
      addDyingImage("units/archer-die4");
  } else if (type == ARMAGEDDON) {
      addStandingImage("units/armageddon");
      setAllAttributes(65, 0, 25, 10, 2, 2);
      addDyingImage("units/armageddon-die1");
      addDyingImage("units/armageddon-die2");
      addDyingImage("units/armageddon-die3");
      addDyingImage("units/armageddon-die4");
      addDyingImage("units/armageddon-die5");
      addDyingImage("units/armageddon-die6");
  } else if (type == BAT) {
      addStandingImage("units/bat-se-1");
      addStandingImage("units/bat-se-2");
      addStandingImage("units/bat-se-3");
      addStandingImage("units/bat-se-4");
      addStandingImage("units/bat-se-5");
      addStandingImage("units/bat-se-4");
      addStandingImage("units/bat-se-3");
      addStandingImage("units/bat-se-2");
      setAllAttributes(25, 0, 5, 3, 4, 4);
  } else if (type == BLADEMASTER) {
      addStandingImage("units/blademaster");
      setAllAttributes(45, 0, 20, 7, 4, 3);
      addDyingImage("units/blademaster-die-1");
      addDyingImage("units/blademaster-die-2");
      addDyingImage("units/blademaster-die-3");
      addDyingImage("units/blademaster-die-4");
      addDyingImage("units/blademaster-die-5");
      addDyingImage("units/blademaster-die-6");
      addDyingImage("units/blademaster-die-7");
  } else if (type == CAVESPIDER) {
      addStandingImage("units/cavespider");
      setAllAttributes(35, 0, 10, 4, 3, 1);
      addDyingImage("units/cavespider-die-1");
      addDyingImage("units/cavespider-die-2");
  } else if (type == FLANKER) {
      addStandingImage("units/flanker");
      setAllAttributes(10, 0, 7, 2, 5, 3);
  } else if (type == PILLAGER) {
      addStandingImage("units/pillager");
      setAllAttributes(40, 0, 18, 6, 3, 5);
   } else if (type == SERGEANT) {
      addStandingImage("units/sergeant");
      setAllAttributes(50, 0, 17, 10, 2, 3);
   } else if (type == SKELETON) {
      addStandingImage("units/skeleton");
      setAllAttributes(35, 0, 15, 8, 2, 2);
      addDyingImage("units/skeleton-dying-1");
      addDyingImage("units/skeleton-dying-2");
      addDyingImage("units/skeleton-dying-3");
      addDyingImage("units/skeleton-dying-4");
      addDyingImage("units/skeleton-dying-5");
      addDyingImage("units/skeleton-dying-6");
      addDyingImage("units/skeleton-dying-7");
  } else if (type == WOLF_RIDER) {
      addStandingImage("units/wolf-rider");
      setAllAttributes(28, 0, 13, 7, 5, 4);
   }
}
