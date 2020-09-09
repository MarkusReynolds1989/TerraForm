P=main
OBJECTS= main.o 
CFLAGS= `pkg-config --cflags raylib glib-2.0` -g -Wall -std=gnu2x -O3
LDLIBS= `pkg-config --libs raylib glib-2.0`


$(P): $(OBJECTS)
