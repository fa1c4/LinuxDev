# makefile for PDFlab testing

CC=g++
CLFAGS=-c -Wall -g -I.
LFLAGS=-lm
LZFLAGS=-lm

all: testDelete

testDelete: testDelete.o
	$(CC) testDelete.o -o testDelete.elf $(LFLAGS)

testDelete.o: testDelete.cpp
	$(CC) $(CLFAGS) testDelete.cpp -o testDelete.o

clean:
	rm *.o *.elf
