CC=g++
CFLAGS=-c -Wall -Werror -g -I/usr/include/mongocxx -I/usr/include/bsoncxx
LDFLAGS=-lm -lrestbed -L/usr/lib/x86_64-linux-gnu -lmongocxx -lbsoncxx --std=c++17


all: mWebQueryMongo

mWebQueryMongo: mWebQueryMongo.o
	$(CC) mWebQueryMongo.o -o mWebQueryMongo.elf $(LDFLAGS)
mWebQueryMongo.o: mWebQueryMongo.cpp
	$(CC) $(CFLAGS) mWebQueryMongo.cpp

clean:
	rm *.o *.elf
