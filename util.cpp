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

// 
void increaseId(std::string &id) {
  id[1]++;
  if (id[1] == '9'+1)
    id[1] = 'a';
  else if (id[1] == 'z'+1)
    id[1] = 'A';
  else if (id[1] == 'Z'+1) {
    id[1] = '0';
    id[0]++;
    if (id[0] == '9'+1)
      id[0] = 'a';
    else if (id[0] == 'z'+1)
      id[0] = 'A';
  }
}

// 
void decreaseId(std::string &id) {
  id[1]--;
  if (id[1] == 'A'-1)
    id[1] = 'z';
  else if (id[1] == 'a'-1)
    id[1] = '9';
  else if (id[1] == '0'-1) {
    id[1] = 'Z';
    id[0]--;
    if (id[0] == 'A'-1)
      id[0] = 'z';
    else if (id[0] == 'a'-1)
      id[1] = '9';
  }
}
