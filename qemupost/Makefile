# Build qemupost...

CPP = g++
CC  = gcc
CFLAGS = -Wall -g
CPPFLAGS = -std=c++11 -Wno-deprecated
LFLAGS = -lz

all: qemupost

qemupost: main.o itoa.o
	$(CPP) $(CFLAGS) $(CPPFLAGS) -o qemupost main.o itoa.o $(LFLAGS)

main.o: main.cpp CLI11/CLI11x.hpp itoa.h PPC_Lookup.h
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c main.cpp

itoa.o: itoa.h
	$(CC) $(CFLAGS) -c itoa.c

clean:
	rm *.o qemupost
