# Makefile lab for QueryMongo

CC=g++
CFLAGS=-c -Wall -Werror -g -I/usr/local/include/mongocxx -I/usr/local/include/bsoncxx
LFLAGS=-lm -L/usr/lib/x86_64-linux-gnu -lmongocxx -lbsoncxx --std=c++17
# LFLAGS needs to be put at the end of command

all: QueryMongo

QueryMongo: QueryMongo.o
	$(CC) QueryMongo.o -o QueryMongo.elf $(LFLAGS)

QueryMongo.o: QueryMongo.cpp
	$(CC) $(CFLAGS) QueryMongo.cpp -o QueryMongo.o $(LFLAGS)

clean:
	rm *.o QueryMongo.elf