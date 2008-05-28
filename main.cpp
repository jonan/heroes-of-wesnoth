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
         /// @todo Change version
         cout << "\nHeroes of Wesnoth SVN\n"
              << "\nusage: heroes [OPTIONS]\n"
              << "  -h, --help       prints this message and exits.\n"
              << endl;
         return EXIT_SUCCESS;
      }
   }
   // Start the game engine
   boot();
   // Start the main menu
   startMainMenu();

   return EXIT_SUCCESS;
}
