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
#include "util.hpp"
#include "xml_manager.hpp"

// video_engine
using video_engine::screen;
using video_engine::FACE_RIGHT;

// Constructor
Unit::Unit(const char *type, const int number) {
  master = NULL;
  this->number = number;

  facing_side = FACE_RIGHT;
  sprite = 0;
  num_frames_per_sprite = 3;
  actual_animation = STANDING;
  position = NULL;
  magic_spell = NULL;

  if (strcmp(type,"hero")) {
    this->type = type;
    setCreaturesAttributes(UNITS_XML_FILE);
  }
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
  if (!animations[actual_animation].empty() || actual_animation == ATTACKING)
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

// Returns the number of frames needed to perform the animation.
int Unit::getNumFrames(const int animation) {
  return animations[animation].size()*num_frames_per_sprite;
}

// Makes this creature inflict damage to another creature.
void Unit::damageCreature(Unit &creature) {
  // Calculate the damage
  double damage = (attack*(log(number)+1));
  creature.live -= damage;
  // Make the damage
  while (creature.live <= 0 && creature.number != 0) {
    creature.live = creature.live_max+creature.live;
    creature.number--;
  }
  /**
  // Check if it's a close or distant attack
  bool is_close_attack = false;
  for (int i=N; i<=NW && !is_close_attack; i++)
    is_close_attack = is_close_attack || (position->getConnectedCell(i)->getCreature() == &creature);
  // Set the animations
  setAnimation(ATTACKING);
  if (!is_close_attack) creature.addMagicAnimation(projectiles_type);
  creature.setAnimation(DEFENDING);
  */
}

// Adds a magic animation.
void Unit::addMagicAnimation(const int spell) {
  magic_spell = new SpecialImage;
  magic_spell->frame = 0;
  magic_spell->num_frames_per_sprite = 3;
  magic_spell->position.x = 0;
  magic_spell->position.y = 0;

  // Set the varibles depending of the tipe of item.
  switch (spell) {
    case WHITE_MISSILE:
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-1"));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-2"));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-3"));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-4"));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-5"));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-6"));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-7"));
      magic_spell->image_list.push_back(screen->getImage("projectiles/whitemissile-impact-8"));
      break;
    default:
      // Imposible case
      break;
  }

  magic_spell->position.x = -(magic_spell->image_list[0]->w-72)/2;
  magic_spell->position.y = -(magic_spell->image_list[0]->h-72)/2;
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

// Sets the creature's attributes acording to his type.
void Unit::setCreaturesAttributes(const char *xml_file) {
  TiXmlElement *root = XmlManager::getInstance()->getRootElement(xml_file);

  TiXmlElement *temp = root->FirstChildElement();
  if (type.length() > 2) {
    while( type != temp->Attribute("name") )
      temp = temp->NextSiblingElement();
    type = temp->Attribute("id");
  } else {
    while ( type != temp->Attribute("id") )
      temp = temp->NextSiblingElement();
  }

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
  TiXmlNode *img;
  const char *animation_names[] = { "attacking",
                                    "defending",
                                    "dying",
                                    "idle",
                                    "standing"   };
  for (int i=0; i<NUM_ANIMATIONS; i++) {
    img = NULL;
    while ( (img = images->IterateChildren(animation_names[i], img)) )
      addAnimationImage(img->ToElement()->GetText(), i);
  }
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

  if (!animations[actual_animation].empty()) {
    // Draw the corresponding sprite.
    screen->draw(animations[actual_animation][sprite/num_frames_per_sprite], position);
    sprite++;
    // Check if this was the last sprite and go back to standing if it was.
    if ( (sprite/num_frames_per_sprite) == static_cast<int>(animations[actual_animation].size()) ) {
      sprite = 0;
      actual_animation = STANDING;
    }
    // Draw a spell if it's needed.
    if (magic_spell) {
      unsigned int sprite = magic_spell->frame/magic_spell->num_frames_per_sprite;
      if (sprite == magic_spell->image_list.size()) {
        delete magic_spell;
        magic_spell = NULL;
      } else {
        position.x += magic_spell->position.x;
        position.y += magic_spell->position.y;
        screen->draw(magic_spell->image_list[sprite], position);
        position.x -= magic_spell->position.x;
        position.y -= magic_spell->position.y;
        magic_spell->frame++;
      }
    }
  } else { // The animation is ATTACKING
    // If there's no animation for attack simply get the creature closer to the enemy
    screen->draw(animations[STANDING][0], position);
    sprite++;
    if (sprite == num_frames_per_sprite) {
      sprite = 0;
      actual_animation = STANDING;
    }
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

// Adds an image to a given animation.
void Unit::addAnimationImage(const char *imageName, const int animation) {
  animations[animation].push_back( screen->getImage(imageName) );
}
