# makefile for CPP TCP file socket 

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lboost_regex -lboost_iostreams -lpthread -lboost_system

all: rfc_server rfc_client

rfc_server: rfc_server.o
	$(CC) rfc_server.o -o rfc_server.elf $(LDFLAGS)

rfc_server.o: rfc_server.cpp
	$(CC) $(CFLAGS) rfc_server.cpp -o rfc_server.o

rfc_client: rfc_client.o
	$(CC) rfc_client.o -o rfc_client.elf $(LDFLAGS)

rfc_client.o: rfc_client.cpp	
	$(CC) $(CFLAGS) rfc_client.cpp -o rfc_client.o

clean:
	rm *.o *.elf
	