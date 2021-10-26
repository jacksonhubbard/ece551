CPPFLAGS=-Wall -Werror -std=gnu++98 -pedantic -ggdb3
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRCS))
PROGRAM=code

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)

%.o: %.cpp code.cpp
	g++ -c $(CPPFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~
