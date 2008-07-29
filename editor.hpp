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

#include "macros.hpp"

/// The map editor.
///
/// -no detailed description-
class Editor : public Map {
  public:
    /// @param[in] width Map's width.
    /// @param[in] height Map's height 
    Editor(const int width, const int height); // Constructor

  private:
    // Function to execute when the user clicks on a cell.
    virtual void mouseClick(const int x, const int y);

    // This function is executed in the main loop. If
    // it returns true, the loop ends, else it continues.
    virtual bool frame(void);

    // Does nothing but it's necessary when inheriting from map.
    virtual void nextTurn(void) {};

    // Saves the current map in the file.
    void save(void);
    // Loads the map from the file.
    void load(void);

    // Draws the editor in the screen.
    virtual void draw(void);

    char actual_terrain;
    bool end_editor;

    DISALLOW_COPY_AND_ASSIGN(Editor);
};

// Starts the editor.
void startEditor(void);

#endif // EDITOR_HPP
