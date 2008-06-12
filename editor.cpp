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

#include <fstream>

#include "cell.hpp"
#include "editor.hpp"
#include "events.hpp"

using namespace std;

// Function to execute when the user clicks on a cell.
void editor::mouseClick(const int x, const int y) {
   if (battleMap[x][y].getTerrain() != actualTerrain)
      setTerrain(actualTerrain, x, y);
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool editor::frame(void) {
   if (keys[SDLK_ESCAPE]) {
      while (keys[SDLK_ESCAPE]) input->readInput();
      endEditor = true;
   } else if (keys[SDLK_F1]) save();
   else if (keys[SDLK_F2]) load();
   else if (keys[SDLK_0]) actualTerrain = '0';
   else if (keys[SDLK_1]) actualTerrain = '1';
   else if (keys[SDLK_2]) actualTerrain = '2';
   else if (keys[SDLK_3]) actualTerrain = '3';
   else if (keys[SDLK_4]) actualTerrain = '4';
   else if (keys[SDLK_5]) actualTerrain = '5';
   else if (keys[SDLK_6]) actualTerrain = '6';
   else if (keys[SDLK_SPACE]) {
      while (keys[SDLK_SPACE]) input->readInput();
      softenMap();
   } else {
      moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
      draw();
   }
   return endEditor;
}

// Saves the current map in the file.
void editor::save(void) {
   ofstream file("maps/editor");

   for (int y=0; y<height; y++) {
      for (int x=0; x<width; x++)
         file << battleMap[x][y].getTerrain();
      file << '\n';
   }

   file.close();
}

// Loads the map from the file.
void editor::load(void) {
   // Delete the current map
   for (int i=0; i<width; i++)
      delete [] battleMap[i];
   delete [] battleMap;
   // The cell where the mouse was is deleted
   // so the pointer needs to be removed.
   mouseOverCell = NULL;
   // Create a new map
   battleMap = new cell*[width];
   for (int i=0; i<width; i++)
      battleMap[i] = new cell[height];
   connectCells();
   // Load the file
   ifstream file("maps/editor");
   char temp;
   int i = 0;
   int j = 0;
   while (j<height) {
      file.get(temp);
      if (temp != '\n') {
         setTerrain(temp, i, j);
         i++;
         if (i == width) {
            i = 0;
            j++;
         }
      }
   }
   file.close();
   // Make the hole map visible
   for (int x=0; x<width; x++)
      for (int y=0; y<height; y++)
         battleMap[x][y].calculateView(1);
}

// Constructor
editor::editor(const int width, const int height) : map(width, height) {
   setTerrain(FLAT_GRASS);
   actualTerrain = FLAT_GRASS;
   endEditor = false;

   // Make the hole map visible
   for (int x=0; x<width; x++)
      for (int y=0; y<height; y++)
         battleMap[x][y].calculateView(1);
}

// Starts the editor.
void startEditor(void) {
   editor map(30,20);
   map.start();
}
