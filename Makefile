OBJECTS = battle.o boot.o cell.o editor.o events.o graphics.o hero.o hero_type.o \
	image.o loop.o main.o map.o map_soft.o map_terrain.o menu.o menu_main.o \
	mission.o timer.o ttf.o unit.o unit_type.o world.o
SDL_LIBS = -lSDL -lSDL_ttf -lSDL_image -lSDL_gfx
CFLAGS = -c -g -Wall
CC = g++

heroes : $(OBJECTS)
	$(CC) -g $(SDL_LIBS) -o heroes $(OBJECTS)

battle.o : battle.cpp battle.hpp cell.hpp events.hpp graphics.hpp hero.hpp map.hpp unit.hpp
	$(CC) $(CFLAGS) battle.cpp

boot.o : boot.cpp boot.hpp events.hpp graphics.hpp
	$(CC) $(CFLAGS) boot.cpp

cell.o : cell.cpp cell.hpp graphics.hpp unit.hpp
	$(CC) $(CFLAGS) cell.cpp

editor.o : editor.cpp editor.hpp cell.hpp events.hpp map.hpp
	$(CC) $(CFLAGS) editor.cpp

events.o : events.cpp events.hpp
	$(CC) $(CFLAGS) events.cpp

graphics.o : graphics.cpp graphics.hpp image.hpp timer.hpp ttf.hpp
	$(CC) $(CFLAGS) graphics.cpp

hero.o : hero.cpp hero.hpp graphics.hpp unit.hpp
	$(CC) $(CFLAGS) hero.cpp

hero_type.o : hero_type.cpp hero.hpp unit.hpp
	$(CC) $(CFLAGS) hero_type.cpp

image.o : image.cpp image.hpp graphics.hpp
	$(CC) $(CFLAGS) image.cpp

loop.o : loop.cpp loop.hpp events.hpp graphics.hpp timer.hpp
	$(CC) $(CFLAGS) loop.cpp

main.o : main.cpp boot.hpp menu_main.hpp
	$(CC) $(CFLAGS) main.cpp

map.o : map.cpp map.hpp cell.hpp events.hpp graphics.hpp timer.hpp unit.hpp
	$(CC) $(CFLAGS) map.cpp

map_soft.o : map_soft.cpp map.hpp cell.hpp graphics.hpp
	$(CC) $(CFLAGS) map_soft.cpp

map_terrain.o : map_terrain.cpp map.hpp cell.hpp graphics.hpp
	$(CC) $(CFLAGS) map_terrain.cpp

menu.o : menu.cpp menu.hpp graphics.hpp
	$(CC) $(CFLAGS) menu.cpp

menu_main.o : menu_main.cpp menu_main.hpp battle.hpp boot.hpp editor.hpp events.hpp graphics.hpp loop.hpp menu.hpp mission.hpp
	$(CC) $(CFLAGS) menu_main.cpp

mission.o : mission.cpp mission.hpp hero.hpp map.hpp unit.hpp world.hpp
	$(CC) $(CFLAGS) mission.cpp

timer.o : timer.cpp timer.hpp
	$(CC) $(CFLAGS) timer.cpp

ttf.o : ttf.cpp ttf.hpp
	$(CC) $(CFLAGS) ttf.cpp

unit.o : unit.cpp unit.hpp graphics.hpp
	$(CC) $(CFLAGS) unit.cpp

unit_type.o : unit_type.cpp unit.hpp
	$(CC) $(CFLAGS) unit_type.cpp

world.o : world.cpp world.hpp battle.hpp cell.hpp events.hpp hero.hpp unit.hpp map.hpp
	$(CC) $(CFLAGS) world.cpp

.PHONY : clean
clean :
	-rm heroes $(OBJECTS) *~