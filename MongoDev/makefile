# Makefile lab for MongoConnectTest

CC=g++
CFLAGS=-c -Wall -Werror -g -I/usr/include/mongocxx -I/usr/include/bsoncxx
LFLAGS=-lm -L/usr/lib/x86_64-linux-gnu -lmongocxx -lbsoncxx --std=c++17
# LFLAGS needs to be put at the end of command

all: MongoConnectTest

MongoConnectTest: MongoConnectTest.o
	$(CC) MongoConnectTest.o -o MongoConnectTest.elf $(LFLAGS)

MongoConnectTest.o: MongoConnectTest.cpp
	$(CC) $(CFLAGS) MongoConnectTest.cpp -o MongoConnectTest.o $(LFLAGS)

clean:
	rm *.o MongoConnectTest.elf