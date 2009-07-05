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

#include "xml_manager.hpp"

#include "tinyxml/tinyxml.h"

#include "util.hpp"

// Singleton pattern constructor
XmlManager* XmlManager::getInstance(void) {
  static XmlManager instance;
  return &instance;
}

// Destructor
XmlManager::~XmlManager(void) {
  std::list<TiXmlDocument*>::iterator it;
  std::list<TiXmlDocument*>::iterator it_end = xml_files.end();
  for (it = xml_files.begin(); it != it_end; it++) {
    free( (*it)->GetUserData() );
    delete (*it);
  }
}

// 
TiXmlDocument* XmlManager::loadFile(const char *file_name) {
  TiXmlDocument *file = new TiXmlDocument(file_name);
  file->LoadFile();
  xml_files.push_back(file);
  return file;
}

// 
void XmlManager::setIds(TiXmlDocument *file) {
  TiXmlElement *root = file->RootElement();

  TiXmlElement *temp = root->FirstChildElement();
  // Set IDs only if it hasn't already have ones
  if ( !temp->Attribute("id") ) {
    std::string id = "00";
    while (temp) {
      temp->SetAttribute("id", id.c_str());
      increaseId(id);
      temp = temp->NextSiblingElement();
    }
    file->SetUserData(strdup(id.c_str()));
  }
}

// 
void XmlManager::setNumbers(TiXmlNode *node) {
  TiXmlElement *temp = node->FirstChildElement();
  // Set numbers only if it hasn't already have ones
  if ( !temp->Attribute("num") ) {
    int num = 0;
    char text[4];
    while (temp) {
      sprintf(text, "%i", num);
      temp->SetAttribute("num", text);
      num++;
      temp = temp->NextSiblingElement();
    }
  }
}

// 
TiXmlElement* XmlManager::getRootElement(const char *file_name) {
  return getFile(file_name)->RootElement();
}

// 
const char* XmlManager::getId(const char *name, const char *file) {
  TiXmlElement *temp = getRootElement(file)->FirstChildElement();
  while ( strcmp(name,temp->Attribute("name")) )
    temp = temp->NextSiblingElement();
  return temp->Attribute("id");
}

// 
const char* XmlManager::getName(const char *id, const char *file) {
  TiXmlElement *temp = getRootElement(file)->FirstChildElement();
  while ( strcmp(id,temp->Attribute("id")) )
    temp = temp->NextSiblingElement();
  return temp->Attribute("name");
}

// 
char* XmlManager::getLastId(const char *file_name) {
  return static_cast<char*>(getFile(file_name)->GetUserData());
}

// 
TiXmlDocument* XmlManager::getFile(const char *file_name) {
  bool found = false;
  std::list<TiXmlDocument*>::iterator it;
  std::list<TiXmlDocument*>::iterator it_end = xml_files.end();
  for (it = xml_files.begin(); it != it_end && !found; it++)
    if (!strcmp(file_name, (*it)->Value()))
      found = true;
  it--;
  return (*it);
}
