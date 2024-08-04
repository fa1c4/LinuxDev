# makefile for udpserver 

CC=g++
CLFAGS=-c -Wall -g
LFLAGS=-lboost_regex -lboost_iostreams -lpthread -lboost_system

all: udpServer udpClient

udpServer: udpServer.o
	$(CC) udpServer.o -o udpServer.elf $(LFLAGS)

udpServer.o: udpServer.cpp
	$(CC) $(CLFAGS) udpServer.cpp -o udpServer.o $(LFLAGS)

udpClient: udpClient.o
	$(CC) udpClient.o -o udpClient.elf $(LFLAGS)

udpClient.o: udpClient.cpp
	$(CC) $(CLFAGS) udpClient.cpp -o udpClient.o $(LFLAGS)

clean:
	rm *.o *.elf
	