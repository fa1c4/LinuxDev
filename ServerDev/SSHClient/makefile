# makefile for sshClient

CC=g++
CFLAGS=-c -Wall -g
LFLAGS=-lssh

sshClient: sshClient.o
	$(CC) sshClient.o -o sshClient.elf $(LFLAGS)

sshClient.o: sshClient.cpp
	$(CC) $(CFLAGS) sshClient.cpp -o sshClient.o $(LFLAGS)

clean:
	rm *.o *.elf
