# makefile for processes communication through system V message queue

CC=g++
CLFAGS=-c -Wall -g
LFLAGS=-lpthread -lrt

all: mqSend mqRecv

mqSend: mqSend.o
	$(CC) mqSend.o -o mqSend.elf $(LFLAGS)

mqSend.o: mqSend.cpp
	$(CC) $(CLFAGS) mqSend.cpp -o mqSend.o $(LFLAGS)

mqRecv: mqRecv.o
	$(CC) mqRecv.o -o mqRecv.elf $(LFLAGS)

mqRecv.o: mqRecv.cpp
	$(CC) $(CLFAGS) mqRecv.cpp -o mqRecv.o $(LFLAGS)

clean:
	rm *.o *.elf *.txt
