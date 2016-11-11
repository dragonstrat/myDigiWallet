CC=g++
CFLAGS=-c -Wall -std=c++0x -g
LDFLAGS=
SOURCES=src/main.cc src/myutilities.cc src/myhash.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=src/antifraud

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) src/*.o

