# makefile for gzip decoder demo

CC=g++
CLFAGS=-c -Wall -g -I.
LFLAGS=-lm -lz

all: gzipDecoder

gzipDecoder: gzipDecoder.o
	$(CC) gzipDecoder.o -o gzipDecoder.elf $(LFLAGS)

gzipDecoder.o: gzipDecoder.cpp
	$(CC) $(CLFAGS) gzipDecoder.cpp -o gzipDecoder.o

clean:
	rm *.o *.elf
	