# makefile for POSIX Semaphore test

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lrt -lpthread -std=c++11

all: pshm_create pshm_open

pshm_create: pshm_create.o
	$(CC) pshm_create.o -o pshm_create.elf $(LDFLAGS)
pshm_create.o: pshm_create.cpp
	$(CC) $(CFLAGS) pshm_create.cpp -o pshm_create.o

pshm_open: pshm_open.o
	$(CC) pshm_open.o -o pshm_open.elf $(LDFLAGS)
pshm_open.o: pshm_open.cpp
	$(CC) $(CFLAGS) pshm_open.cpp -o pshm_open.o

clean:
	rm *.o *.elf
