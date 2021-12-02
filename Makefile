CC = g++
CFLAGS = -c -Wall
LDFLAGS = -std=c++11
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = cs375Stars
RM=rm -f

all:	$(EXECUTABLE)

$(EXECUTABLE): main.o 
	$(CC) main.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.cpp 

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)