# makefile for Linux Signals Test
CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-pthread

all: mSignals threadSignals recvSignals sendSignals

mSignals: mSignals.o
	$(CC) mSignals.o -o mSignals.elf $(LDFLAGS)
mSignals.o: mSignals.cpp
	$(CC) $(CFLAGS) mSignals.cpp -o mSignals.o

threadSignals: threadSignals.o
	$(CC) threadSignals.o -o threadSignals.elf $(LDFLAGS)
threadSignals.o: threadSignals.cpp
	$(CC) $(CFLAGS) threadSignals.cpp -o threadSignals.o

recvSignals: recvSignals.o
	$(CC) recvSignals.o -o recvSignals.elf $(LDFLAGS)
recvSignals.o: recvSignals.cpp
	$(CC) $(CFLAGS) recvSignals.cpp -o recvSignals.o

sendSignals: sendSignals.o
	$(CC) sendSignals.o -o sendSignals.elf $(LDFLAGS)
sendSignals.o: sendSignals.cpp
	$(CC) $(CFLAGS) sendSignals.cpp -o sendSignals.o

clean:
	rm *.o *.elf
	