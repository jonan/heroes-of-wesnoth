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

#ifndef UNIT_HPP
#define UNIT_HPP

#include "graphics.hpp"

class unit {
   protected:
      int live, live_max;
      int magic, magic_max;

      int fis_def, fis_attack;
      int mag_def, mag_attack;

      int movement;

      char *image;
      bool selected;

   public:
      //unit(char tipe[20]);
      void setAllAtributes(int live, int magic, int des_fis, int def_mag, int attack_fis, int attack_mag, int movement);
/* ----------------------------------------------------------------------------------------------------------------------- */
      void setImage(const char *imageName);
      void draw(graphics *screen, SDL_Rect *position);
      bool isSelected();
      void select();
      void unselect();
      int getMovement();
};

#endif

/* Last Version: Jonan */
