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

#include "world.hpp"

#include "battle.hpp"
#include "cell.hpp"
#include "events.hpp"
#include "hero.hpp"

// events_engine
using events_engine::input;
using events_engine::keys;
using events_engine::mouse;
using events_engine::MOUSE_BUTTON;
using events_engine::NORMAL_CURSOR;

// Constructor
World::World(const char *map_file) : Map(map_file) {
  smoothMap();
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
  input->setCursorType(NORMAL_CURSOR);
}

// Puts a hero in the map.
void World::setHero(Hero &hero, const int x, const int y) {
  heroes.push_back(&hero);
  map[x][y].setCreature(&hero);
  map[x][y].calculateView(hero.getVisibility());
}

// Function to execute when the user left clicks on a cell.
void World::mouseLeftClick(const int x, const int y) {
  if ( selected_unit->getPosition() != &map[x][y] ) {
    if ( map[x][y].canMoveHere() || map[x][y].canAttackHere()) {
      moveSelectedCreature(map[x][y]);
      map[x][y].calculateView(static_cast<Hero*>(selected_unit)->getVisibility());

      if ( selected_unit->getPosition() != &map[x][y] ) {
        // Set the battle information
        Hero *selected_hero = static_cast<Hero*>(selected_unit);
        const char *terrain = map[x][y].getTerrainId();
        bool won_battle;
        if (!map[x][y].getCreature()->getMaster()) {
          // Battle against a neutral creature
          const char *creature_type = map[x][y].getCreature()->getId();
          won_battle = createBattle(*selected_hero, creature_type, terrain);
        } else {
          // Battle against a hero
          Hero *enemy_hero = static_cast<Hero*>(map[x][y].getCreature());
          won_battle = createBattle(*selected_hero, *enemy_hero, terrain);
        }
        // Remove losers
        if (won_battle)
          deleteCreature(map[x][y]);
        else
          heroes.remove(selected_hero);
      }

      nextTurn();
    }
  }
}

// Starts the next turn.
void World::nextTurn(void) {
  // Check if the battle has ended
  if (heroes.empty() || number_enemies == 0) end_world = true;
  // If the battle hasn't ended continue
  if (!end_world) {
    heroes.push_back(heroes.front());
    heroes.pop_front();
    selected_unit = *heroes.begin();
    selected_unit->getPosition()->select();
    // Wait until the mouse button is released.
    while (mouse[MOUSE_BUTTON]) input->readInput();
    centerView(*selected_unit);
  }
}

// Removes a unit from the world and deletes it.
void World::deleteCreature(Cell &position) {
  if (!position.getCreature()->getMaster()) {
    delete position.getCreature();
    number_enemies--;
  } else {
    heroes.remove(static_cast<Hero*>(position.getCreature()));
  }
  position.setCreature(NULL);
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
