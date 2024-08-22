CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lpthread

all: RLimit RUsage

RLimit: RLimit.o
	$(CC) RLimit.o -o RLimit.elf $(LDFLAGS)
RLimit.o: RLimit.cpp
	$(CC) $(CFLAGS) RLimit.cpp $(LDFLAGS)

RUsage: RUsage.o
	$(CC) RUsage.o -o RUsage.elf $(LDFLAGS)
RUsage.o: RUsage.cpp
	$(CC) $(CFLAGS) RUsage.cpp $(LDFLAGS)

clean:
	rm *.o *.elf
