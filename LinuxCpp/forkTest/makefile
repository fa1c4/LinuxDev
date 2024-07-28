# makefile for forkMain

CC=g++
CFLAGS=-c -Wall -g -I.
LFLAGS=-lm

all: forkMain

forkMain: forkMain.o
	$(CC) forkMain.o -o forkMain.elf

forkMain.o: forkMain.cpp
	$(CC) $(CFLAGS) forkMain.cpp -o forkMain.o $(LFLAGS)

clean:
	rm *.o *.elf
