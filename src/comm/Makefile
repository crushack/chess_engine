CC=g++
CPPFLAGS=-Wall -g -std=c++11

EXEC = run
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)


# Main target
$(EXEC): $(OBJECTS)


%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@