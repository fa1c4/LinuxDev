CC=g++
CFLAGS=-c -Wall -Werror -g -I/usr/include/mongocxx -I/usr/include/bsoncxx
LDFLAGS=-lm -lrestbed -L/usr/lib/x86_64-linux-gnu -lmongocxx -lbsoncxx --std=c++17


all: WebRestMain

WebRestMain: WebRestMain.o
	$(CC) WebRestMain.o -o WebRestMain.elf $(LDFLAGS)
WebRestMain.o: WebRestMain.cpp
	$(CC) $(CFLAGS) WebRestMain.cpp

clean:
	rm *.o *.elf
