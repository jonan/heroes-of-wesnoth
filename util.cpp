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
along with Heroes of Wesnoth. If not, see <http://www.gnu.org/licenses/>
*/

#include "util.hpp"

// Increases the given char one unit.
void increaseChar(char &ch) {
  ch++;
  if (ch == '9'+1) ch = 'a';
  else if (ch == 'z'+1) ch = 'A';
}

// Decreases the given char one unit.
void decreaseChar(char &ch) {
  ch--;
  if (ch == 'A'-1) ch = 'z';
  else if (ch == 'a'-1) ch = '9';
}

// Increases the given ID one unit.
void increaseId(std::string &id) {
  increaseChar(id[1]);
  if (id[1] == 'Z'+1) {
    id[1] = '0';
    increaseChar(id[0]);
  }
}

// Decreases the given ID one unit.
void decreaseId(std::string &id) {
  decreaseChar(id[1]);
  if (id[1] == '0'-1) {
    id[1] = 'Z';
    decreaseChar(id[0]);
  }
}
