# makefile for google protocol API test mArena

CC=g++
CFLAGS=-c -Wall -I/usr/local/include/google/protobuf
LDFLAGS=-L/usr/local/lib -lprotobuf

all: mArena

mArena: mArena.o
	$(CC) mArena.o -o mArena.elf $(LDFLAGS)
mArena.o: mArena.cpp
	$(CC) $(CFLAGS) mArena.cpp -o mArena.o

clean:
	rm *.o *.elf
	