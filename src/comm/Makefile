CC=g++
CPPFLAGS=-Wall -g -std=c++11

EXEC = run
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(wildcard ../util/*.h)

# Main target
$(EXEC): $(OBJECTS)


%.o: %.cpp $(HEADERS)
	$(CC) -c $(CPPFLAGS) $< -o $@