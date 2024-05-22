# Makefile lab for ParallRead

CC=g++
CFLAGS=-c -Wall
LFLAGS=-lm 

all: ParallRead

ParallRead: ParallRead.o
	$(CC) $(LFLAGS) ParallRead.o -o ParallRead

ParallRead.o: ParallRead.cpp
	$(CC) $(CFLAGS) ParallRead.cpp -o ParallRead.o

clean:
	rm *.o ParallRead