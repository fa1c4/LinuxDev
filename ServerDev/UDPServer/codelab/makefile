# makefile for udpserver codelab 

CC=g++
CLFAGS=-c -Wall -g
LFLAGS=-lboost_regex -lboost_iostreams -lpthread -lboost_system

all: RegxTest

RegxTest: RegxTest.o
	$(CC) RegxTest.o -o RegxTest.elf $(LFLAGS)

RegxTest.o: RegxTest.cpp
	$(CC) $(CLFAGS) RegxTest.cpp -o RegxTest.o $(LFLAGS)

clean:
	rm *.o *.elf
	