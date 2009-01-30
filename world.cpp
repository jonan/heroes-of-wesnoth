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
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include "world.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "battle.hpp"
#include "cell.hpp"
#include "events.hpp"
#include "hero.hpp"

// std
using std::cout;
using std::ifstream;
using std::string;
// events_engine
using events_engine::input;
using events_engine::keys;
using events_engine::mouse;
using events_engine::BUTTON;
using events_engine::NORMAL;

// Constructor
World::World(const char *map_file, const int width, const int height) : Map(width, height) {
  // Create a string with the fisical location of the file
  // "map/" + name
  string map = "maps/";
  string file_name(map_file);
  string file_dir = map + file_name;

  ifstream file(file_dir.c_str());
  if (file.fail()) {
    cout << "Error opening map \"" << map_file << "\"\n\n";
    exit(EXIT_FAILURE);
  }

  // Set the terrain
  char temp;
  int i = 0;
  int j = 0;
  while (j<height) {
    file.get(temp);
    if (temp != '\n') {
      setTerrain(temp, &battle_map[i][j]);
      i++;
      if (i == width) {
        i = 0;
        j++;
      }
    }
  }

  file.close();

  setEnemies(map_file);
  setItems(map_file);
  softenMap();

  turn = -1;
  end_world = false;
}

// Destructor
World::~World(void) {
  for (int x=0; x<width; x++)
    for (int y=0; y<height; y++)
      if (battle_map[x][y].getCreature())
        delete battle_map[x][y].getCreature();

  // Make sure the cursors's type is normal
  input->setCursorType(NORMAL);
}

// Puts a hero in the map.
void World::setHero(Hero &player, const int x, const int y) {
  players.push_back(&player);
  battle_map[x][y].setCreature(&player);
  battle_map[x][y].calculateView(player.getVisibility());
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool World::frame(void) {
  Map::frame();
  if (keys[SDLK_ESCAPE]) {
    keys[SDLK_ESCAPE] = false;
    end_world = true;
  } else if (!end_world) {
    if (keys[SDLK_c]) centerView(*selected_unit);
    draw();
    moveMouse();
  }
  return end_world;
}

// Function to execute when the user left clicks on a cell.
void World::mouseLeftClick(const int x, const int y) {
  if ( selected_unit->getPosition() != &battle_map[x][y] ) {
    if ( battle_map[x][y].canMoveHere() ) {
      moveCreature(battle_map[x][y]);
      battle_map[x][y].calculateView(players[turn]->getVisibility());
      nextTurn();
    } else if ( battle_map[x][y].canAttackHere() ) {
      if ( battle_map[x][y].getCreature()->getMaster() != selected_unit->getMaster() ) {
        moveCreature(battle_map[x][y]);
        battle_map[x][y].calculateView(players[turn]->getVisibility());

        // Set the battle information
        Hero *player = static_cast<Hero*>(selected_unit);
        char creatureType = battle_map[x][y].getCreature()->getType();
        char terrain = battle_map[x][y].getTerrain();
        // Start the battle
        if ( createBattle(*player, creatureType, terrain) )
          deleteCreature(battle_map[x][y]);
        else
          players[turn] = NULL;

        nextTurn();
      }
    }
  }
}

// Starts the next turn.
void World::nextTurn(void) {
  // Check if the battle has ended
  if (players[0]==NULL || number_enemies == 0) end_world = true;
  // If the battle hasn't ended continue
  if (!end_world) {
    turn++;
    if (turn == static_cast<int>(players.size())) turn = 0;
    selected_unit = players[turn];
    selected_unit->getPosition()->select();
    // Wait until the mouse button is released.
    while (mouse[BUTTON]) input->readInput();
    centerView(*selected_unit);
  }
}

// Puts the enemies in the map.
void World::setEnemies(const char *map_file) {
  // Create a string with the fisical location of the file
  // "map/" + name + "_creatures"
  string map = "maps/";
  string fileName(map_file);
  string fileDir = map + map_file + "_creatures";

  ifstream file(fileDir.c_str());
  if (file.fail()) {
    cout << "Error opening map \"" << map_file << "\"\n\n";
    exit(EXIT_FAILURE);
  }

  // Set the enemies
  number_enemies = 0;
  char temp;
  int i = 0;
  int j = 0;
  while (j<height) {
    file.get(temp);
    if (temp != '\n') {
      if (temp != '-') {
        Unit *creature;
        creature = new Unit(temp, 0);
        battle_map[i][j].setCreature(creature);
        number_enemies++;
      }
      i++;
      if (i == width) {
        i = 0;
        j++;
      }
    }
  }

  file.close();
}

// Puts the items on the map.
void World::setItems(const char *map_file) {
  // Create a string with the fisical location of the file
  // "map/" + name + "_items"
  string map = "maps/";
  string fileName(map_file);
  string fileDir = map + map_file + "_items";

  ifstream file(fileDir.c_str());
  if (file.fail()) {
    cout << "Error opening map \"" << map_file << "\"\n\n";
    exit(EXIT_FAILURE);
  }

  // Set the items
  char temp;
  int i = 0;
  int j = 0;
  while (j<height) {
    file.get(temp);
    if (temp != '\n') {
      if (temp != '-')
        setItem(temp, battle_map[i][j]);
      i++;
      if (i == width) {
        i = 0;
        j++;
      }
    }
  }

  file.close();
}

// Removes a unit from the world and deletes it.
void World::deleteCreature(Cell &position) {
  delete position.getCreature();
  position.setCreature(NULL);
  number_enemies--;
}
