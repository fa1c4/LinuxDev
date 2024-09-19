# makefile for CPP TCP socket 

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lboost_regex -lboost_iostreams -lpthread -lboost_system

all: iostream_server iostream_client

iostream_server: iostream_server.o
	$(CC) iostream_server.o -o iostream_server.elf $(LDFLAGS)

iostream_server.o: iostream_server.cpp
	$(CC) $(CFLAGS) iostream_server.cpp -o iostream_server.o

iostream_client: iostream_client.o
	$(CC) iostream_client.o -o iostream_client.elf $(LDFLAGS)

iostream_client.o: iostream_client.cpp	
	$(CC) $(CFLAGS) iostream_client.cpp -o iostream_client.o

clean:
	rm *.o *.elf
	