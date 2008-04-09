/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007  Jon Ander Peñalba <jonan88@gmail.com>

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
      setImage("bat-se-1", 1);
      setImage("bat-se-2", 2);
      setImage("bat-se-3", 3);
      setImage("bat-se-4", 4);
      setImage("bat-se-5", 5);
      setImage("bat-se-4", 6);
      setImage("bat-se-3", 7);
      setImage("bat-se-2", 8);
      setAllAttributes(25, 5, 3, 2, 5, 1, 4, 4);
   } else if (type == SERGEANT) {
      setImage("sergeant");
      setAllAttributes(50, 0, 10, 5, 15, 0, 2, 3);
   } else if (type == SKELETON) {
      setImage("skeleton");
      setAllAttributes(50, 0, 10, 5, 15, 0, 2, 2);
   }
}
