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

#include "battle.hpp"
#include "cell.hpp"
#include "events.hpp"
#include "hero.hpp"

// events_engine
using events_engine::input;
using events_engine::keys;
using events_engine::mouse;
using events_engine::BUTTON;
using events_engine::NORMAL;

// Constructor
World::World(const char *map_file) : Map(map_file) {
  softenMap();
  turn = 0;
  end_world = false;
  // Count the number of enemies
  number_enemies = 0;
  for (int x=0; x<map_width; x++)
    for (int y=0; y<map_height; y++)
      if (map[x][y].getCreature())
        number_enemies++;
}

// Destructor
World::~World(void) {
  deleteCreatures();
  // Make sure the cursors's type is normal
  input->setCursorType(NORMAL);
}

// Puts a hero in the map.
void World::setHero(Hero &player, const int x, const int y) {
  players.push_back(&player);
  map[x][y].setCreature(&player);
  map[x][y].calculateView(player.getVisibility());
}

// Function to execute when the user left clicks on a cell.
void World::mouseLeftClick(const int x, const int y) {
  if ( selected_unit->getPosition() != &map[x][y] ) {
    if ( map[x][y].canMoveHere() ) {
      moveSelectedCreature(map[x][y]);
      map[x][y].calculateView(players[turn]->getVisibility());
      nextTurn();
    } else if ( map[x][y].canAttackHere() ) {
      moveSelectedCreature(map[x][y]);
      map[x][y].calculateView(players[turn]->getVisibility());

      // Set the battle information
      Hero *player = static_cast<Hero*>(selected_unit);
      char creatureType = map[x][y].getCreature()->getType();
      char terrain = map[x][y].getTerrain();
      // Start the battle
      if ( createBattle(*player, creatureType, terrain) )
        deleteCreature(map[x][y]);
      else
        players[turn] = NULL;

      nextTurn();
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
    if (turn == players.size()) turn = 0;
    selected_unit = players[turn];
    selected_unit->getPosition()->select();
    // Wait until the mouse button is released.
    while (mouse[BUTTON]) input->readInput();
    centerView(*selected_unit);
  }
}

// Removes a unit from the world and deletes it.
void World::deleteCreature(Cell &position) {
  delete position.getCreature();
  position.setCreature(NULL);
  number_enemies--;
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool World::frame(void) {
  adjustVisibleMap();
  if (keys[SDLK_ESCAPE]) {
    keys[SDLK_ESCAPE] = false;
    end_world = true;
  } else if (!end_world) {
    if (keys[SDLK_c]) centerView(*selected_unit);
    draw();
    updateMouse();
  }
  return end_world;
}
