OBJECTS = events.o graphics.o hero.o image.o main.o map.o menu.o ttf.o unit.o
SDL_LIBS = -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image


heroes : $(OBJECTS)
	g++ -g $(SDL_LIBS) -o heroes $(OBJECTS)

events.o : events.cpp events.hpp
	g++ -c -g events.cpp

graphics.o : graphics.cpp graphics.hpp image.o ttf.o
	g++ -c -g graphics.cpp

hero.o : hero.cpp hero.hpp unit.o
	g++ -c -g hero.cpp

image.o : image.hpp image.cpp
	g++ -c -g image.cpp

main.o : main.cpp events.o hero.o map.o menu.o
	g++ -c -g main.cpp

map.o : map.hpp map.cpp unit.o
	g++ -c -g map.cpp

menu.o : menu.hpp menu.cpp graphics.o
	g++ -c -g menu.cpp

ttf.o : ttf.hpp ttf.cpp
	g++ -c -g ttf.cpp

unit.o : unit.hpp unit.cpp graphics.o
	g++ -c -g unit.cpp

.PHONY : clean
clean :
	-rm heroes $(OBJECTS) *~