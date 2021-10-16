CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
code: code.o
	g++ -o code code.o
code.o: code.cpp code.h
	g++ $(CPPFLAGS) -c code.cpp code.h
