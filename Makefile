FLAGS = -Wall -ansi -pedantic
all:
	g++ $(FLAGS) -c	Cell.cpp
	g++ $(FLAGS) -c Line.cpp
	g++ $(FLAGS) -o quine Check.cpp *.o
