OBJECTS = battle.o boot.o events.o graphics.o hero.o image.o loop.o main.o map.o menu.o menu_main.o timer.o ttf.o unit.o
SDL_LIBS = -lSDL -lSDL_ttf -lSDL_image
CFLAGS = -c -g
CC = g++

heroes : $(OBJECTS)
	$(CC) -g $(SDL_LIBS) -o heroes $(OBJECTS)

battle.o : battle.cpp battle.hpp events.hpp graphics.hpp hero.hpp map.hpp timer.hpp
	$(CC) $(CFLAGS) battle.cpp

boot.o : boot.cpp boot.hpp events.hpp graphics.hpp
	$(CC) $(CFLAGS) boot.cpp

events.o : events.cpp events.hpp
	$(CC) $(CFLAGS) events.cpp

graphics.o : graphics.cpp graphics.hpp image.hpp ttf.hpp
	$(CC) $(CFLAGS) graphics.cpp

hero.o : hero.cpp hero.hpp unit.hpp
	$(CC) $(CFLAGS) hero.cpp

image.o : image.cpp image.hpp
	$(CC) $(CFLAGS) image.cpp

loop.o : loop.cpp loop.hpp events.hpp graphics.hpp timer.hpp
	$(CC) $(CFLAGS) loop.cpp

main.o : main.cpp boot.hpp menu_main.hpp
	$(CC) $(CFLAGS) main.cpp

map.o : map.cpp map.hpp graphics.hpp unit.hpp
	$(CC) $(CFLAGS) map.cpp

menu.o : menu.cpp menu.hpp graphics.hpp
	$(CC) $(CFLAGS) menu.cpp

menu_main.o : menu_main.cpp menu_main.hpp battle.hpp boot.hpp events.hpp graphics.hpp loop.hpp menu.hpp
	$(CC) $(CFLAGS) menu_main.cpp

timer.o : timer.cpp timer.hpp
	$(CC) $(CFLAGS) timer.cpp

ttf.o : ttf.cpp ttf.hpp
	$(CC) $(CFLAGS) ttf.cpp

unit.o : unit.cpp unit.hpp graphics.hpp
	$(CC) $(CFLAGS) unit.cpp

.PHONY : clean
clean :
	-rm heroes $(OBJECTS) *~