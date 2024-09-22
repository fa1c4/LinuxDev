# makefile for paramPack
CC=g++
CFLAGS=-c -Wall -g -I./
LDFLAGS=-std=c++11

all: paramPack

paramPack: paramPack.o
	$(CC) paramPack.o -o paramPack.elf $(LDFLAGS)

paramPack.o: paramPack.cpp
	$(CC) $(CFLAGS) paramPack.cpp -o paramPack.o $(LDFLAGS)

clean:
	rm *.elf *.o
