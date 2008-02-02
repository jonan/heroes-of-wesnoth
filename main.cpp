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

/// @file
/// The main function.
/// @author Jonan

#include <iostream>

#include "boot.hpp"
#include "menu_main.hpp"

using namespace std;

int main(int argc, char *argv[]) {
   // Check the programs arguments
   for (int i=1; i<argc; i++) {
      const string val(argv[i]);
      if (val == "-h" || val == "--help") {
         cout << "Heroes of Wesnoth v0.0.1\n"
         << "\nusage: heroes [OPTIONS]\n"
         << "  -h, --help       prints this message and exits.\n";
         return 0;
      }
   }
   // Start the game
   boot();
   startMainMenu();
   quit();
   return 0;
}
