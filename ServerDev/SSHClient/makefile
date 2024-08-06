# makefile for sshClient and sshCMD

CC=g++
CFLAGS=-c -Wall -g
LFLAGS=-lssh -lpthread

all: sshClient sshCMD

sshClient: sshClient.o
	$(CC) sshClient.o -o sshClient.elf $(LFLAGS)

sshClient.o: sshClient.cpp
	$(CC) $(CFLAGS) sshClient.cpp -o sshClient.o $(LFLAGS)

sshCMD: sshCMD.o
	$(CC) sshCMD.o -o sshCMD.elf $(LFLAGS)

sshCMD.o: sshCMD.cpp
	$(CC) $(CFLAGS) sshCMD.cpp -o sshCMD.o $(LFLAGS)

clean:
	rm *.o *.elf
