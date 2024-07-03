# Makefile lab for ConstructTest

CC=g++
CFLAGS=-c -Wall
LFLAGS=-lm

all: ConstructTest

ConstructTest: ConstructTest.o
	$(CC) $(LFLAGS) ConstructTest.o -o ConstructTest.elf

ConstructTest.o: ConstructTest.cpp
	$(CC) $(CFLAGS) ConstructTest.cpp -o ConstructTest.o

clean:
	rm *.o ConstructTest.elf
