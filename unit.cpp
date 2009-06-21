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

#include "unit.hpp"

#include <cmath>

#include "tinyxml/tinyxml.h"

#include "cell.hpp"
#include "graphics.hpp"
#include "structs.hpp"

// video_engine
using video_engine::screen;
using video_engine::FACE_RIGHT;

// Constructor
Unit::Unit(const char type, const int number) {
  this->number = number;

  facing_side = FACE_RIGHT;
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

// Destructor
Unit::~Unit(void) {
 delete magic_spell;
}

// Starts a given animation.
void Unit::setAnimation(const int animation) {
  actual_animation = animation;
  /* If this unit has no sprite for the given animation
    go back to STANDING (ATTACKING has a default animation). */
  if (animations[actual_animation].size() > 0 || actual_animation == ATTACKING)
    sprite = 0;
  else
    actual_animation = STANDING;
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
  bool is_close_attack = false;
  for (int i=N; i<=NW && !is_close_attack; i++)
    is_close_attack = is_close_attack || (position->getConnectedCell(i)->getCreature() == &creature);
  // Set the animations
  setAnimation(ATTACKING);
  if (!is_close_attack) creature.addMagicAnimation(projectiles_type);
  creature.setAnimation(DEFENDING);
}

// Draws the creature in the given position.
void Unit::draw(SDL_Rect &position) {
  drawUnit(position);
  // Draw the number of units
  if (number>0) {
    char text[3];
    sprintf(text, "%i", number);
    screen->write(text, position.x+17, position.y+52);
  }
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

// Sets the creature's attributes acording to his type.
void Unit::setCreaturesAttributes(void) {
  TiXmlDocument document("config/config_units.xml");
  document.LoadFile();

  TiXmlElement *root = document.RootElement();

  bool found = false;
  TiXmlElement *temp = root->FirstChildElement();
  for (; temp && !found; temp = temp->NextSiblingElement()) {
    if ( type == temp->Attribute("id")[1] )
      found = true;
  }

  if (found) {
    temp = temp->PreviousSibling()->ToElement();
    // Set the attributes
    TiXmlNode *attributes = temp->FirstChild("attributes");
    int live, movement, attack, agility;
    int projectiles_type, projectiles;
    live = atoi(attributes->FirstChildElement("live")->GetText());
    movement = atoi(attributes->FirstChildElement("movement")->GetText());
    attack = atoi(attributes->FirstChildElement("attack")->GetText());
    agility = atoi(attributes->FirstChildElement("agility")->GetText());
    projectiles_type = atoi(attributes->FirstChildElement("projectiles")->FirstChildElement("type")->GetText());
    projectiles = atoi(attributes->FirstChildElement("projectiles")->FirstChildElement("number")->GetText());
    setAllAttributes(live, movement, attack, agility, projectiles, projectiles_type);
    // Set the images
    TiXmlNode *images = temp->FirstChild("images");
    TiXmlElement *img;
    const char *animation_names[] = { "attacking",
                                      "defending",
                                      "dying",
                                      "idle",
                                      "standing"   };
    for (int i=0; i<NUM_ANIMATIONS; i++)
      for (img = images->FirstChildElement(animation_names[i]); img; img = img->NextSiblingElement(animation_names[i]))
        addAnimationImage(img->GetText(), i);
  }
}

// Adds an image to the standing animation.
void Unit::addAnimationImage(const char *imageName, const int animation) {
  animations[animation].push_back( screen->getImage(imageName) );
}

// Draws the creature in the given position.
void Unit::drawUnit(SDL_Rect &position) {
  // Get closer to the enemy when attacking
  if (actual_animation == ATTACKING) {
    if (facing_side == FACE_RIGHT)
      position.x += 10;
    else
      position.x -= 10;
  } else if (actual_animation == STANDING) { // Might start idle animation
    int random_number = rand() % 1000;
    if (random_number == 0) setAnimation(IDLE);
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
}
