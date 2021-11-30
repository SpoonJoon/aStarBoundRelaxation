CC = g++
CFLAGS = -c -Wall
LDFLAGS = 
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = cs375Stars
RM=rm -f

all:	$(EXECUTABLE)

$(EXECUTABLE): main.o 
	g++ $(LDFLAGS) main.o -o $(EXECUTABLE)

main.o: main.cpp
	g++ -c main.cpp 

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)