# makefile for Atomic Operation Library

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lpthread -std=c++11

all: mThreadReadfile mThreadCalculate

mThreadReadfile: mThreadReadfile.o
	$(CC) mThreadReadfile.o -o mThreadReadfile.elf $(LDFLAGS)
mThreadReadfile.o: mThreadReadfile.cpp
	$(CC) $(CFLAGS) mThreadReadfile.cpp -o mThreadReadfile.o

mThreadCalculate: mThreadCalculate.o
	$(CC) mThreadCalculate.o -o mThreadCalculate.elf $(LDFLAGS)
mThreadCalculate.o: mThreadCalculate.cpp
	$(CC) $(CFLAGS) mThreadCalculate.cpp -o mThreadCalculate.o

clean:
	rm *.o *.elf
	