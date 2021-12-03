CC = g++
CFLAGS = -c -Wall
LDFLAGS = -std=c++11
SOURCES = astar.cpp astar_graph.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = cs375Stars
RM=rm -f

all:	$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SOURCES)

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)