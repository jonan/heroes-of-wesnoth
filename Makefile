OBJECTS = events.o graphics.o hero.o image.o main.o map.o menu.o timer.o ttf.o unit.o
SDL_LIBS = -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image
CFLAGS = -c -g
CC = g++

heroes : $(OBJECTS)
	$(CC) -g $(SDL_LIBS) -o heroes $(OBJECTS)

events.o : events.cpp events.hpp
	$(CC) $(CFLAGS) events.cpp

graphics.o : graphics.cpp graphics.hpp image.hpp ttf.hpp
	$(CC) $(CFLAGS) graphics.cpp

hero.o : hero.cpp hero.hpp unit.hpp
	$(CC) $(CFLAGS) hero.cpp

image.o : image.hpp image.cpp
	$(CC) $(CFLAGS) image.cpp

main.o : main.cpp events.hpp graphics.hpp hero.hpp map.hpp menu.hpp timer.hpp
	$(CC) $(CFLAGS) main.cpp

map.o : map.hpp map.cpp graphics.hpp unit.hpp
	$(CC) $(CFLAGS) map.cpp

menu.o : menu.hpp menu.cpp graphics.hpp
	$(CC) $(CFLAGS) menu.cpp

timer.o : timer.hpp timer.cpp
	$(CC) $(CFLAGS) timer.cpp

ttf.o : ttf.hpp ttf.cpp graphics.hpp
	$(CC) $(CFLAGS) ttf.cpp

unit.o : unit.hpp unit.cpp graphics.hpp
	$(CC) $(CFLAGS) unit.cpp

.PHONY : clean
clean :
	-rm heroes $(OBJECTS) *~