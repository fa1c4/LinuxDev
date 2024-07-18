# makefile for object linking

CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lm

OBJ_LIST=linkObj.o nodebase.o

all: linkObj

linkObj: $(OBJ_LIST)
	$(CC) $(LDFLAGS) $(OBJ_LIST) -o linkObj.elf

linkObj.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o linkObj.o

nodebase.o: nodebase.cpp
	$(CC) $(CFLAGS) nodebase.cpp -o nodebase.o

clean:
	rm *.o *.elf 
