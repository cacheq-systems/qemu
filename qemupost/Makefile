# Build qemupost...

CPP = g++
CC  = gcc
CFLAGS = -Wall
CPPFLAGS = -std=c++11 -Wno-deprecated

all: qemupost

qemupost: main.o itoa.o
	$(CPP) $(CFLAGS) $(CPPFLAGS) -o qemupost main.o itoa.o

main.o: CLI11/CLI11x.hpp itoa.h PPC_Lookup.h
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c main.cpp

itoa.o: itoa.h
	$(CC) $(CFLAGS) -c itoa.c
