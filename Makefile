# Heroes of Wesnoth - http://heroesofwesnoth.sf.net
# Copyright (C) 2007-2008 Jon Ander Peñalba <jonan88@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
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

OBJECTS = battle.o boot.o cell.o editor.o events.o graphics.o hero.o hero_type.o \
	image.o loop.o main.o map.o map_item.o map_soft.o map_terrain.o menu.o \
	menu_main.o mission.o timer.o ttf.o unit.o unit_magic.o unit_type.o world.o
SDL_LIBS = -lSDL -lSDL_ttf -lSDL_image -lSDL_gfx
CFLAGS = -c -g -Wall
CC = g++

heroes : $(OBJECTS)
	$(CC) -g -Wall $(SDL_LIBS) -o heroes $(OBJECTS)

battle.o : battle.cpp battle.hpp cell.hpp events.hpp graphics.hpp loop.hpp hero.hpp \
	macros.hpp map.hpp structs.hpp timer.hpp unit.hpp
	$(CC) $(CFLAGS) battle.cpp

boot.o : boot.cpp boot.hpp events.hpp graphics.hpp macros.hpp
	$(CC) $(CFLAGS) boot.cpp

cell.o : cell.cpp cell.hpp graphics.hpp macros.hpp structs.hpp unit.hpp
	$(CC) $(CFLAGS) cell.cpp

editor.o : editor.cpp editor.hpp cell.hpp events.hpp graphics.hpp loop.hpp macros.hpp \
	map.hpp structs.hpp unit.hpp
	$(CC) $(CFLAGS) editor.cpp

events.o : events.cpp events.hpp graphics.hpp macros.hpp
	$(CC) $(CFLAGS) events.cpp

graphics.o : graphics.cpp graphics.hpp events.hpp image.hpp macros.hpp timer.hpp ttf.hpp
	$(CC) $(CFLAGS) graphics.cpp

hero.o : hero.cpp hero.hpp graphics.hpp macros.hpp structs.hpp unit.hpp
	$(CC) $(CFLAGS) hero.cpp

hero_type.o : hero_type.cpp hero.hpp macros.hpp structs.hpp unit.hpp
	$(CC) $(CFLAGS) hero_type.cpp

image.o : image.cpp image.hpp graphics.hpp macros.hpp
	$(CC) $(CFLAGS) image.cpp

loop.o : loop.cpp loop.hpp events.hpp graphics.hpp timer.hpp macros.hpp
	$(CC) $(CFLAGS) loop.cpp

main.o : main.cpp boot.hpp menu_main.hpp
	$(CC) $(CFLAGS) main.cpp

map.o : map.cpp map.hpp cell.hpp events.hpp graphics.hpp loop.hpp macros.hpp structs.hpp \
	unit.hpp
	$(CC) $(CFLAGS) map.cpp

map_item.o : map_item.cpp map.hpp cell.hpp graphics.hpp loop.hpp macros.hpp structs.hpp
	$(CC) $(CFLAGS) map_item.cpp

map_soft.o : map_soft.cpp map.hpp cell.hpp graphics.hpp loop.hpp macros.hpp structs.hpp
	$(CC) $(CFLAGS) map_soft.cpp

map_terrain.o : map_terrain.cpp map.hpp cell.hpp graphics.hpp loop.hpp macros.hpp structs.hpp
	$(CC) $(CFLAGS) map_terrain.cpp

menu.o : menu.cpp menu.hpp graphics.hpp macros.hpp
	$(CC) $(CFLAGS) menu.cpp

menu_main.o : menu_main.cpp menu_main.hpp battle.hpp boot.hpp editor.hpp events.hpp \
	graphics.hpp loop.hpp macros.hpp map.hpp menu.hpp mission.hpp structs.hpp
	$(CC) $(CFLAGS) menu_main.cpp

mission.o : mission.cpp mission.hpp hero.hpp loop.hpp macros.hpp map.hpp structs.hpp unit.hpp \
	world.hpp
	$(CC) $(CFLAGS) mission.cpp

timer.o : timer.cpp timer.hpp macros.hpp
	$(CC) $(CFLAGS) timer.cpp

ttf.o : ttf.cpp ttf.hpp graphics.hpp macros.hpp
	$(CC) $(CFLAGS) ttf.cpp

unit.o : unit.cpp unit.hpp cell.hpp graphics.hpp macros.hpp structs.hpp
	$(CC) $(CFLAGS) unit.cpp

unit_magic.o : unit_magic.cpp unit.hpp graphics.hpp macros.hpp structs.hpp
	$(CC) $(CFLAGS) unit_magic.cpp

unit_type.o : unit_type.cpp unit.hpp macros.hpp structs.hpp
	$(CC) $(CFLAGS) unit_type.cpp

world.o : world.cpp world.hpp battle.hpp cell.hpp events.hpp hero.hpp loop.hpp macros.hpp \
	map.hpp structs.hpp unit.hpp
	$(CC) $(CFLAGS) world.cpp

.PHONY : clean
clean :
	-rm heroes $(OBJECTS) *~
