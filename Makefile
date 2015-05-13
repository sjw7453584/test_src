CC=g++
SRC=$(wildcard *.cpp)
objects=$(SRC:.cpp=.o)
CPPFLAGS=-g -O0

all:$(objects)
	$(CC) $(CPPFLAGS) $< -o test

$(objects):%.o:%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@


clean:
	rm *.o test
