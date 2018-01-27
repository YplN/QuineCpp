FLAGS = -Wall -ansi -pedantic
all:
	g++ $(FLAGS) -c	Cell.cpp
	g++ $(FLAGS) -c Line.cpp
	g++ $(FLAGS) -c Card.cpp
	g++ $(FLAGS) -c Game.cpp
	g++ $(FLAGS) -std=c++11 -o quine Check.cpp *.o
