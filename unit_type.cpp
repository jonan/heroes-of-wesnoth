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

#include "unit_type.hpp"

// Sets the creatures attributes acording to his type.
void setCreaturesAttributes(unit* creature) {
   char *type;
   type = creature->getType();

   if (type == "skeleton") {
      creature->setImage("skeleton");
      creature->setAllAttributes(50, 0, 10, 5, 15, 0, 2, 2);
   } else if (type == "orc") {
      /// @todo Add more types of units
   }
}
