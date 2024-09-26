# makefile for shared memory demo

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lrt -lpthread -lboost_system -std=c++11

all: create_shared_vector open_shared_vector

create_shared_vector: create_shared_vector.o
	$(CC) create_shared_vector.o -o create_shared_vector.elf $(LDFLAGS)
create_shared_vector.o: create_shared_vector.cpp
	$(CC) $(CFLAGS) create_shared_vector.cpp -o create_shared_vector.o $(LDFLAGS)

open_shared_vector: open_shared_vector.o
	$(CC) open_shared_vector.o -o open_shared_vector.elf $(LDFLAGS)
open_shared_vector.o: open_shared_vector.cpp
	$(CC) $(CFLAGS) open_shared_vector.cpp -o open_shared_vector.o $(LDFLAGS)

clean:
	rm *.o *.elf
