# This file is part of Heroes of Wesnoth.
# Copyright (C) 2007, 2008, 2009 Jon Ander Peñalba <jonan88@gmail.com>
#
# Heroes of Wesnoth is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>

# Global variables
OBJECTS = battle.o \
          boot.o \
          cell.o \
          editor.o \
          events.o \
          graphics.o \
          hero.o \
          hero_type.o \
          image.o \
          loop.o \
          main.o \
          map.o \
          map_item.o \
          map_soft.o \
          map_terrain.o \
          menu.o \
          menu_main.o \
          mission.o \
          ttf.o \
          unit.o \
          unit_magic.o \
          unit_type.o \
          world.o
SDL_LIBS = -lSDL -lSDL_ttf -lSDL_image -lSDL_gfx
CFLAGS = -c -g -Wall
CC = g++
EXE = heroes

# Headers dependencies
BATTLE = battle.hpp \
         $(MAP)

BOOT = boot.hpp

CELL = cell.hpp \
       $(MACROS)

EDITOR = editor.hpp \
         $(MAP)

EVENTS = events.hpp \
         $(MACROS)

GRAPHICS = graphics.hpp \
           $(MACROS)

HERO = hero.hpp \
       $(UNIT)

IMAGE = image.hpp \
        $(GRAPHICS)

LOOP = loop.hpp \
       $(MACROS)

MACROS = macros.hpp

MAP = map.hpp \
      $(LOOP) \
      $(STRUCTS)

MENU = menu.hpp \
       $(LOOP)

MENU_MAIN = menu_main.hpp

MISSION = mission.hpp

STRUCTS = structs.hpp

TIMER = timer.hpp \
        $(MACROS)

TTF = ttf.hpp \
      $(GRAPHICS)

UNIT = unit.hpp \
       $(MACROS)

WORLD = world.hpp \
        $(MAP)

# Build dependencies
$(EXE) : $(OBJECTS)
	$(CC) -g -Wall $(SDL_LIBS) -o heroes $(OBJECTS)

battle.o : battle.cpp $(BATTLE) \
           $(CELL) \
           $(EVENTS) \
           $(GRAPHICS) \
           $(HERO) \
           $(TIMER)
	$(CC) $(CFLAGS) battle.cpp

boot.o : boot.cpp $(BOOT) \
         $(EVENTS) \
         $(GRAPHICS)
	$(CC) $(CFLAGS) boot.cpp

cell.o : cell.cpp $(CELL) \
         $(GRAPHICS) \
         $(STRUCTS) \
         $(UNIT)
	$(CC) $(CFLAGS) cell.cpp

editor.o : editor.cpp $(EDITOR) \
           $(CELL) \
           $(EVENTS) \
           $(GRAPHICS) \
           $(UNIT)
	$(CC) $(CFLAGS) editor.cpp

events.o : events.cpp $(EVENTS) \
           $(GRAPHICS)
	$(CC) $(CFLAGS) events.cpp

graphics.o : graphics.cpp $(GRAPHICS) \
             $(EVENTS) \
             $(IMAGE) \
             $(TIMER) \
             $(TTF)
	$(CC) $(CFLAGS) graphics.cpp

hero.o : hero.cpp $(HERO) \
         $(GRAPHICS) \
         $(STRUCTS)
	$(CC) $(CFLAGS) hero.cpp

hero_type.o : hero_type.cpp $(HERO)
	$(CC) $(CFLAGS) hero_type.cpp

image.o : image.cpp $(IMAGE)
	$(CC) $(CFLAGS) image.cpp

loop.o : loop.cpp $(LOOP) \
         $(EVENTS) \
         $(GRAPHICS) \
         $(TIMER)
	$(CC) $(CFLAGS) loop.cpp

main.o : main.cpp \
         $(BOOT) \
         $(MENU_MAIN)
	$(CC) $(CFLAGS) main.cpp

map.o : map.cpp $(MAP) \
        $(CELL) \
        $(EVENTS) \
        $(GRAPHICS) \
        $(UNIT)
	$(CC) $(CFLAGS) map.cpp

map_item.o : map_item.cpp $(MAP) \
             $(CELL) \
             $(GRAPHICS)
	$(CC) $(CFLAGS) map_item.cpp

map_soft.o : map_soft.cpp $(MAP) \
             $(CELL) \
             $(GRAPHICS)
	$(CC) $(CFLAGS) map_soft.cpp

map_terrain.o : map_terrain.cpp $(MAP) \
                $(CELL) \
                $(GRAPHICS)
	$(CC) $(CFLAGS) map_terrain.cpp

menu.o : menu.cpp $(MENU) \
         $(EVENTS) \
         $(GRAPHICS)
	$(CC) $(CFLAGS) menu.cpp

menu_main.o : menu_main.cpp $(MENU_MAIN) \
              $(BATTLE) \
              $(BOOT) \
              $(EDITOR) \
              $(EVENTS) \
              $(GRAPHICS) \
              $(MENU) \
              $(MISSION)
	$(CC) $(CFLAGS) menu_main.cpp

mission.o : mission.cpp $(MISSION) \
            $(HERO) \
            $(WORLD)
	$(CC) $(CFLAGS) mission.cpp

ttf.o : ttf.cpp $(TTF)
	$(CC) $(CFLAGS) ttf.cpp

unit.o : unit.cpp $(UNIT) \
         $(CELL) \
         $(GRAPHICS) \
         $(STRUCTS)
	$(CC) $(CFLAGS) unit.cpp

unit_magic.o : unit_magic.cpp $(UNIT) \
               $(GRAPHICS) \
               $(STRUCTS)
	$(CC) $(CFLAGS) unit_magic.cpp

unit_type.o : unit_type.cpp $(UNIT)
	$(CC) $(CFLAGS) unit_type.cpp

world.o : world.cpp $(WORLD) \
          $(BATTLE) \
          $(CELL) \
          $(EVENTS) \
          $(HERO)
	$(CC) $(CFLAGS) world.cpp

# Make options
.PHONY : all clean

all: clean
	make

clean :
	rm -f *~ $(EXE) $(OBJECTS)

