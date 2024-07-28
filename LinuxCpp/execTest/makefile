# makefile for mainProcess and subProcess

CC=g++
CFLAGS=-c -Wall -g -I.
LFLAGS=-lm

all: mainProcess subProcess

mainProcess: mainProcess.o
	$(CC) mainProcess.o -o mainProcess.elf

mainProcess.o: mainProcess.cpp
	$(CC) $(CFLAGS) mainProcess.cpp -o mainProcess.o $(LFLAGS)

subProcess: subProcess.o
	$(CC) subProcess.o -o subProcess.elf

subProcess.o: subProcess.cpp
	$(CC) $(CFLAGS) subProcess.cpp -o subProcess.o $(LFLAGS)

clean:
	rm *.o *.elf
