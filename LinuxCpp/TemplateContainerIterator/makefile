# make file for templateContainerIter

CC=g++
CFLAGS=-c -Wall -g
LFLAGS=-lm

all:templContainerIter

templContainerIter: templContainerIter.o
	$(CC) templContainerIter.o -o templContainerIter.elf

templContainerIter.o: ContainerTest.cpp
	$(CC) $(CFLAGS) ContainerTest.cpp -o templContainerIter.o $(LFLAGS)

clean:
	rm *.o *.elf
