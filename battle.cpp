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

#include "battle.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "timer.hpp"
#include "unit.hpp"

// Function to execute when the cell where the mouse is over is detected.
void battle::mouseOver(int x, int y, int button) {
   battleMap[x][y].putMouse();
   mouseOverCell = &battleMap[x][y];
   if ( button == 1  &&  selectedCell != &battleMap[x][y] ) {
      if (selectedCell) {
         if ( battleMap[x][y].canMoveHere() ) {
            battleMap[x][y].setCreature( selectedCell->getCreature() );
            selectedCell->unselect();
            selectedCell->setCreature(NULL);
         } else
            selectedCell->unselect();
      }
      selectedCell = battleMap[x][y].select();
   }
}

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool battle::frame(void) {
   if (keys[SDLK_ESCAPE]) return true;
   moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   draw();
   return false;
}

// Returns the creature that has the next turn.
unit* battle::nextTurn(void) {

}

// Puts the enemy creatures in the map.
void battle::setCreatures(unit **creatures, int number) {
   if ( number <= 9 ) {
      for (int i=0; i<number; i++) {
         battleMap[sizeX-1][i].setCreature(creatures[i]);
      }
   }
}

// Constructor
battle::battle(hero *player, unit **enemies, int numberEnemies) : map(18, 9) {
   this->player = player;
   creatures = enemies;
   numberCreatures = numberEnemies;
   totalUnits = numberEnemies + player->getNumberCreatures();
   turns = new int[totalUnits];
   // Set the turns
   /*for (int i=0; i<totalUnits; i++) turns[i] = i;
   for (int i=totalUnits; i>0; i++) {
      for (int j=0; j<totalUnits; j++) {
         if (true);
      }
   }*/

   setHero(player);
   setCreatures(creatures, numberCreatures);
   setTerrain("grassland-r1");
}

// Starts the battle.
void battle::start(void) {
   screen->erase();

   /// @todo use the loop function in loop.hpp
   bool done = false;
   timer fps;

   while (!done) {
      fps.start();
      input->readInput();
      done = frame();
      /*if (input->getType() == SYSTEM)
         if (input->getSystemType() == QUIT)
            done = true;*/
      screen->update();
      fps.end(30);
   }
}

// Creates and starts a battle.
void createBattle(void) {
   hero player(FIGHTER);
   unit *creature[9];

   for (int i=0; i<9; i++) {
      creature[i] = new unit(SKELETON, 5);
   }

   battle war(&player, creature, 9);
   war.start();
}
