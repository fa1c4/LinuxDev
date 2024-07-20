# make file for templateContainerTest

CC=g++
CFLAGS=-c -Wall -g
LFLAGS=-lm

all:templContainerTest

templContainerTest: templContainerTest.o
	$(CC) templContainerTest.o -o templContainerTest.elf

templContainerTest.o: ContainerTest.cpp
	$(CC) $(CFLAGS) ContainerTest.cpp -o templContainerTest.o $(LFLAGS)

clean:
	rm *.o *.elf
