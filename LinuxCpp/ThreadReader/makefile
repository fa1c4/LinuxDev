# makefile for thread reader

GXX=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lpthread -std=c++11

all: mThreadReader

mThreadReader: mThreadReader.o
	$(GXX) mThreadReader.o -o mThreadReader.elf $(LDFLAGS)

mThreadReader.o: mThreadReader.cpp
	$(GXX) $(CFLAGS) mThreadReader.cpp -o mThreadReader.o

clean:
	rm *.o *.elf
	