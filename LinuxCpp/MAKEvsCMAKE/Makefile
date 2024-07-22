# Makefile lab for ParallRead

CC=g++
CFLAGS=-c -Wall
LFLAGS=-lm -pthread -std=c++11

all: ParallRead

ParallRead: ParallRead.o
	$(CC) $(LFLAGS) ParallRead.o -o ParallRead

ParallRead.o: ParallRead.cpp
	$(CC) $(CFLAGS) ParallRead.cpp -o ParallRead.o

clean:
	rm *.o ParallRead.elf

# make for singleRead
# all: singleRead
# 
# singleRead: singleRead.o
# 	$(CC) $(LFLAGS) singleRead.o -o singleRead
# 
# singleRead.o: singleRead.cpp
# 	$(CC) $(CFLAGS) singleRead.cpp -o singleRead.o
# 
# clean:
# 	rm *.o singleRead.elf
