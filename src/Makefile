CC=g++
CPPFLAGS=-Wall -g -std=c++11

EXEC = run
SOURCES = $(wildcard **/*.o)
DIRECTORIES = $(sort $(dir $(wildcard */)))
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): directies chess

directies:
	@$(foreach dir, $(DIRECTORIES), make -C $(dir);)

# Main target
chess: $(SOURCES) Main.cpp
	$(CC) $(CPPFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@