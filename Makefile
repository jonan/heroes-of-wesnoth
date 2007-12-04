OBJECTS = events.o graphics.o hero.o image.o main.o map.o menu.o ttf.o unit.o
SDL_LIBS = -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image
CFLAGS = -c -g
CC = g++

heroes : $(OBJECTS)
	$(CC) -g $(SDL_LIBS) -o heroes $(OBJECTS)

events.o : events.cpp events.hpp
	$(CC) $(CFLAGS) events.cpp

graphics.o : graphics.cpp graphics.hpp image.o ttf.o
	$(CC) $(CFLAGS) graphics.cpp

hero.o : hero.cpp hero.hpp unit.o
	$(CC) $(CFLAGS) hero.cpp

image.o : image.hpp image.cpp
	$(CC) $(CFLAGS) image.cpp

main.o : main.cpp events.o hero.o map.o menu.o
	$(CC) $(CFLAGS) main.cpp

map.o : map.hpp map.cpp unit.o
	$(CC) $(CFLAGS) map.cpp

menu.o : menu.hpp menu.cpp graphics.o
	$(CC) $(CFLAGS) menu.cpp

ttf.o : ttf.hpp ttf.cpp
	$(CC) $(CFLAGS) ttf.cpp

unit.o : unit.hpp unit.cpp graphics.o
	$(CC) $(CFLAGS) unit.cpp

.PHONY : clean
clean :
	-rm heroes $(OBJECTS) *~