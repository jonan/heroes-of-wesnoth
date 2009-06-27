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

/// @file
/// 
/// @author Jonan

#ifndef XML_MANAGER_HPP
#define XML_MANAGER_HPP

#include <list>

#include "macros.hpp"

const char HEROES_XML_FILE[]  = "config/config_heroes.xml";
const char ITEMS_XML_FILE[]   = "config/config_items.xml";
const char TERRAIN_XML_FILE[] = "config/config_terrain.xml";
const char UNITS_XML_FILE[]   = "config/config_units.xml";

class TiXmlDocument;
class TiXmlElement;

/// 
class XmlManager {
  public:
    static XmlManager* getInstance(void); // Singleton pattern constructor
    ~XmlManager(void); // Destructor

    /// 
    void loadFile(const char *file_name);

    /// 
    TiXmlElement* getRootElement(const char *file_name);

    /// 
    char* getLastId(const char *file_name);

  private:
    XmlManager(void) {} // Constructor

    // 
    TiXmlDocument* getFile(const char *file_name);

    // 
    void setIds(TiXmlDocument* file);

    std::list<TiXmlDocument*> xml_files;

    DISALLOW_COPY_AND_ASSIGN(XmlManager);
};

#endif // XML_MANAGER_HPP
