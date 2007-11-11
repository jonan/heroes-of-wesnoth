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

#include "map.hpp"

// class cell

// Constructor
cell::cell(void) {
   creature = NULL;
   mouseOver = false;
   selected = false;
   for (int i=0; i<6; i++) {
      conectedCell[i] = NULL;
   }
}

void cell::setPos(SDL_Rect position) {
   this->position = position;
}

void cell::setTerrain(SDL_Surface *terrain) {
   this->terrain = terrain;
}

void cell::setCreature(unit *creature) {
   this->creature = creature;
}

SDL_Rect cell::getPos(void) {
   return position;
}

unit* cell::getCreature(void) {
   return creature;
}

// If the creature in the cell is selected, returns the
// movement, else returns 0
int cell::draw(graphics *screen) {
   screen->draw(terrain, &position);
   if (mouseOver) screen->draw("alpha", &position);
   if (creature) creature->draw(screen, &position);

   if (selected) 
      return creature->getMovement();
   else
      return 0;
}

/*void cell::putMouse() {
   mouseOver = true;
}

void cell::removeMouse() {
   mouseOver = false;
}

void cell::select() {
   selected = true;
}

void cell::unselect() {
   selected = false;
}*/

// ---End---

// class map

// Constructor
map::map(void) {
   SDL_Rect terrainPos;

   terrainPos.x = 17;
   terrainPos.y = 41;
   terrainPos.w = 72;
   terrainPos.h = 72;

   // For creating a battle map grid
   // Top Left.......0, 0
   // Top Right.....17, 0
   // Bottom Left....0, 8
   // Bottom Right..17, 8
   for (int x=0; x<18; x++) {
      for (int y=0; y<9; y++) {
         battleMap[x][y].setPos(terrainPos);
         battleMap[x][y].setCreature(NULL);
         terrainPos.y+=72;
      }
      if ( (x%2)==1 ) {terrainPos.y=41;}
      else {terrainPos.y=77;}
      terrainPos.x+=54;
   }

   selectedCell=NULL;
}

void map::setTerrain(const char terrainImgName[20], graphics *screen) {
   terrainBase = screen->getImage(terrainImgName);

   for (int x=0; x<18; x++)
      for (int y=0; y<9; y++) {
         battleMap[x][y].setTerrain(terrainBase);
         //battle_map[x][y].removeMouse();
         //battle_map[x][y].unselect();
      }
}

void map::setHero(unit *player) {
   battleMap[0][4].setCreature(player);
}

// Draws the map in the screen.
void map::draw(graphics *screen) {
   for (int x=0; x<18; x++) {
      for (int y=0; y<9; y++) {
         battleMap[x][y].draw(screen);
      }
   }
}

/*void map::selectMove(int x, int y, int move, graphics *screen) {
   if (x<18 && y<9 && x>=0 && y>=0) {
      battle_map[x][y].putMouse();
      battle_map[x][y].draw(screen);
   }
   if (move!=0) {
      selectMove(x-1, y, move-1, screen);
      selectMove(x, y-1, move-1, screen);
      selectMove(x-1, y-1, move-1, screen);
      selectMove(x+1, y, move-1, screen);
      selectMove(x, y+1, move-1, screen);
      selectMove(x+1, y+1, move-1, screen);
   }
}

void map::mousePos(int x, int y, int button, graphics *screen) {
   SDL_Rect cell_position;
   int i=0, j=0, move;

   do {
      cell_position = battle_map[i][j].getPos();
      i++;
   } while (x > cell_position.x);
   do {
      cell_position = battle_map[i][j].getPos();
      j++;
   } while (y > cell_position.y);
   i-=2;
   j-=2;
   if (selectedCell) {
      selectedCell->removeMouse();
      selectedCell->draw(screen);
   }
   if (i<0) i=0;
   if (j<0) j=0;
   if ( i<18 && j<9 ) {
      battle_map[i][j].putMouse();
      if (button==1 && battle_map[i][j].getCreature()!=NULL) {
         battle_map[i][j].select();
      } else battle_map[i][j].unselect();
      move=battle_map[i][j].draw(screen);
      if (move!=0) selectMove(i, j, move, screen);
      selectedCell = &battle_map[i][j];
   }
}*/

// ---End---

/* Last Version: Jonan */
