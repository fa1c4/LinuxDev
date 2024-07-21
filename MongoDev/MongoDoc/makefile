# Makefile lab for MongoDocUpdate

CC=g++
CFLAGS=-c -Wall -Werror -g -I/usr/local/include/mongocxx -I/usr/local/include/bsoncxx
LFLAGS=-lm -L/usr/lib/x86_64-linux-gnu -lmongocxx -lbsoncxx --std=c++17
# LFLAGS needs to be put at the end of command

all: MongoDocUpdate

MongoDocUpdate: MongoDocUpdate.o
	$(CC) MongoDocUpdate.o -o MongoDocUpdate.elf $(LFLAGS)

MongoDocUpdate.o: MongoDocUpdate.cpp
	$(CC) $(CFLAGS) MongoDocUpdate.cpp -o MongoDocUpdate.o $(LFLAGS)

clean:
	rm *.o MongoDocUpdate.elf