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
   /// @todo Add more types of units
   if (type == BAT) {
      addStandingImage("bat-se-1");
      addStandingImage("bat-se-2");
      addStandingImage("bat-se-3");
      addStandingImage("bat-se-4");
      addStandingImage("bat-se-5");
      addStandingImage("bat-se-4");
      addStandingImage("bat-se-3");
      addStandingImage("bat-se-2");
      setAllAttributes(25, 5, 3, 2, 5, 1, 4, 4);
   } else if (type == SERGEANT) {
      addStandingImage("sergeant");
      setAllAttributes(50, 0, 10, 5, 15, 0, 2, 3);
   } else if (type == SKELETON) {
      addStandingImage("skeleton");
      setAllAttributes(50, 0, 10, 5, 15, 0, 2, 2);
   }
}
