/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007-2008 Jon Ander Peñalba <jonan88@gmail.com>

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

#include "unit.hpp"

#include <cmath>

#include "cell.hpp"
#include "graphics.hpp"

// video_engine
using video_engine::screen;
using video_engine::OPAQUE;
using video_engine::NONE;

// Constructor
Unit::Unit(const char type, const int number) {
  this->number = number;

  facing_side = RIGHT;
  sprite = 0;
  actual_animation = STANDING;
  magic_spell = NULL;

  if (type != -1) { // It should only be -1 when the unit is a hero.
    this->type = type;
    setCreaturesAttributes();
    master = NULL;
  }

  position = NULL;
}

// Makes the unit face the given side
void Unit::setFacingSide(const int facing_side) {
  if (this->facing_side != facing_side) {
    this->facing_side = facing_side;
    /* Adds at the end of each deque all the images but
      facing the other way, then erases the original ones */
    std::deque<SDL_Surface*>::iterator initialEnd;
    unsigned int initialSize;

    for (int i=0; i<NUM_ANIMATIONS; i++) {
      initialEnd = animations[i].end();
      initialSize = animations[i].size();
      // Add new images
      for (unsigned int j=0; j<initialSize; j++)
        animations[i].push_back( screen->face(facing_side, animations[i][j]) );
      // Erase previous images
      animations[i].erase(animations[i].begin(), initialEnd);
    }
  }
}

// Attacks a given unit.
void Unit::attackCreature(Unit &creature) {
  // Calculate the damage
  double damage = (attack*(log(number)+1));
  creature.live -= damage;
  // Make the damage
  while (creature.live <= 0 && creature.number != 0) {
    creature.live = creature.live_max+creature.live;
    creature.number--;
  }
  // Check if it's a close or distant attack
  bool is_next = false;
  for (int i=N; i<=NW && !is_next; i++)
    is_next = is_next || (position->getConnectedCell(i)->getCreature() == &creature);
  // Set the animations
  if (is_next) {
    startAnimation(ATTACKING);
    creature.startAnimation(DEFENDING);
  } else {
    startAnimation(ATTACKING);
    creature.addMagicAnimation(projectiles_type);
    creature.startAnimation(DEFENDING);
  }
}

// Draws the creature in the given position.
void Unit::draw(SDL_Rect &position) {
  // Get closer to the enemy when attacking
  if (actual_animation == ATTACKING) {
    if (facing_side == RIGHT)
      position.x += 10;
    else
      position.x -= 10;
  } else if (actual_animation == STANDING) { // Might start idle animation
    int random_number = rand() % 1000;
    if (random_number == 0) startAnimation(IDLE);
  }
  if (animations[actual_animation].size() > 0) {
    // Draw the corresponding sprite.
    screen->draw(animations[actual_animation][sprite/NUM_FRAMES_FOR_SPRITE], position);
    sprite++;
    // Check if this was the last sprite and go back to standing if it was.
    if ( (sprite/NUM_FRAMES_FOR_SPRITE) == static_cast<int>(animations[actual_animation].size()) ) {
      sprite = 0;
      actual_animation = STANDING;
    }
    // Draw a spell if it's needed.
    if (magic_spell) {
      position.x += magic_spell->position.x;
      position.y += magic_spell->position.y;
      screen->draw(magic_spell->image_list[magic_spell->sprite/NUM_FRAMES_FOR_SPRITE], position);
      position.x -= magic_spell->position.x;
      position.y -= magic_spell->position.y;
      magic_spell->sprite++;
      if (magic_spell->sprite/NUM_FRAMES_FOR_SPRITE == magic_spell->image_list.size()) {
        delete magic_spell;
        magic_spell = NULL;
      }
    }
  } else { // The animation is ATTACKING
    // If there's no animation for attack simply get the creature closer to the enemy
    screen->draw(animations[STANDING][0], position);
    sprite++;
    if (sprite == NUM_FRAMES_FOR_SPRITE) {
      sprite = 0;
      actual_animation = STANDING;
    }
  }
  // Draw the number of units
  if (number>0) {
    char text[3];
    sprintf(text, "%i", number);
    screen->write(text, position.x+17, position.y+52);
  }
}

// Starts a given animation.
void Unit::startAnimation(const int animation) {
  actual_animation = animation;
  /* If this unit has no sprite for the given animation
    go back to STANDIGN (ATTACKING has a default animation). */
  if (animations[actual_animation].size() > 0 || actual_animation == ATTACKING)
    sprite = 0;
  else
    actual_animation = STANDING;
}

// Sets all the unit's attributes.
void Unit::setAllAttributes(const int live, const int movement,
                            const int attack, const int agility,
                            const int projectiles, const int projectiles_type
                           ) {
  this->live = live;
  live_max = live;
  this->movement = movement;
  this->attack = attack;
  this->agility = agility;
  this->projectiles = projectiles;
  this->projectiles_type = projectiles_type;
}

// Adds an image to the standing animation.
void Unit::addAnimationImage(const char *imageName, const int animation) {
  animations[animation].push_back( screen->getImage(imageName, OPAQUE, NONE, 0) );
}
