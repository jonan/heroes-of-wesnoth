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

/// @file
/// Structs used in different parts of the game.
/// @author Jonan

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <deque>

#include <SDL/SDL.h>

/// Struct to store coordinates.
///
/// -no detailed description-
struct Coordinates {
  int x;
  int y;
};

/// Stores information of special terrains
///
/// -no detailed description-
struct SpecialImage {
  std::deque<SDL_Surface*> image_list;
  Coordinates position;
  unsigned int sprite;
};

#endif // STRUCTS_HPP
