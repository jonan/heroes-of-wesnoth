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

/// @file
/// Map Editor Functions.
/// @author Jonan

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "map.hpp"

/// The map editor.
///
/// -no detailed description-
class editor : public map {
   private:
      char actualTerrain;
      bool end;

      // Function to execute when the user clicks on a cell.
      void mouseClick(const int x, const int y);

      // This function is executed in the main loop. If
      // it returns true, the loop ends, else it continues.
      bool frame(void);

      // Does nothing but it's necessary when inheriting from map.
      void nextTurn(void) {};

   public:
      /// @param[in] width Map's width.
      /// @param[in] height Map's height 
      editor(const int width, const int height); // Constructor
};

void startEditor(void);

#endif // EDITOR_HPP
