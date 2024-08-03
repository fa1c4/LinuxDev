# makefile for udpserver codelab 

CC=g++
CLFAGS=-c -Wall -g
LFLAGS=-lboost_regex -lboost_iostreams -lpthread -lboost_system

all: RegxTest MultiTest

RegxTest: RegxTest.o
	$(CC) RegxTest.o -o RegxTest.elf $(LFLAGS)

RegxTest.o: RegxTest.cpp
	$(CC) $(CLFAGS) RegxTest.cpp -o RegxTest.o $(LFLAGS)

MultiTest: MultiTest.o
	$(CC) MultiTest.o -o MultiTest.elf $(LFLAGS)

MultiTest.o: MultiTest.cpp
	$(CC) $(CLFAGS) MultiTest.cpp -o MultiTest.o $(LFLAGS)

clean:
	rm *.o *.elf
	