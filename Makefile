CC = gcc 
CFLAGS = -g -O -Wall
LIB = -ldsm -lpthread -lrt -lcurses -lm

OBSBIN = ./

SOURCES = gltmonitor.c gltAntMonitor.c  help.c metrology.c

OBJECTS = gltmonitor.o gltAntMonitor.o  help.o  metrology.o

all: gltmonitor

clean:
	rm *.o ./gltmonitor

install: all
	cp gltmonitor $(OBSBIN)/

gltmonitor: $(OBJECTS) ./Makefile
	$(CC) -o gltmonitor $(OBJECTS) $(LIB)

depend: ./Makefile
	$(CC) -MM $(SOURCES) > dependencies

include dependencies
