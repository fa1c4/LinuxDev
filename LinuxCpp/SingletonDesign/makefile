# makefile for thread reader

GXX=g++
CFLAGS=-c -Wall -g -I./
LDFLAGS=-lpthread -std=c++11

all: SingletonReadFile

SingletonReadFile: SingletonReadFile.o SingletonFile.o
	$(GXX) SingletonReadFile.o SingletonFile.o -o SingletonReadFile.elf $(LDFLAGS)

SingletonReadFile.o: SingletonReadFile.cpp SingletonFile.cpp
	$(GXX) $(CFLAGS) SingletonReadFile.cpp -o SingletonReadFile.o
	$(GXX) $(CFLAGS) SingletonFile.cpp -o SingletonFile.o

clean:
	rm *.o *.elf
	