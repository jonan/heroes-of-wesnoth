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
void XmlManager::loadFile(const char *file_name) {
  TiXmlDocument *file = new TiXmlDocument(file_name);
  file->LoadFile();
  setIds(file);
  xml_files.push_back(file);
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

// 
void XmlManager::setIds(TiXmlDocument* file) {
  TiXmlElement *root = file->RootElement();

  std::string id = "00";
  TiXmlElement *temp = root->FirstChildElement();
  for (; temp; temp = temp->NextSiblingElement()) {
    temp->SetAttribute("id", id.c_str());
    increaseId(id);
  }
  file->SetUserData(strdup(id.c_str()));
}
