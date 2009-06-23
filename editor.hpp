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

/// @file
/// The Editor class and a function to start it.
/// @author Jonan

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "map.hpp"

/// The map editor.
class Editor : public Map {
  public:
    /// @param[in] width Map's width.
    /// @param[in] height Map's height.
    /// @param[in] map_file File to save/load the map.
    Editor(const int width, const int height, const char *map_file); // Constructor
    ~Editor(void); // Destructor

  private:
    // Types of editions.
    enum {EDIT_ITEMS, EDIT_TERRAIN, EDIT_UNITS};

    // Function to execute when the user left clicks on a cell.
    virtual void mouseLeftClick(const int x, const int y);
    // Function to execute when the user right clicks on a cell.
    virtual void mouseRightClick(const int x, const int y);

    // Saves the current map in the file.
    void save(void);
    // Loads the map from the file.
    void load(void);

    // Draws the editor in the screen.
    virtual void draw(void);

    // This function is executed in the main loop. If
    // it returns true, the loop ends, else it continues.
    virtual bool frame(void);

    char *map_file;
    char editing_type; // Type of edition selected
    char selected;     // What is selected to be drawn in the map
    bool end_editor;

    DISALLOW_COPY_AND_ASSIGN(Editor);
};

/// Starts the editor.
void startEditor(void);

#endif // EDITOR_HPP
