# Makefile lab for StoreCSV2SQL

CC=g++
CFLAGS=-c -Wall -I/usr/include/cppconn
LFLAGS=-lm -L/usr/lib/x86_64-linux-gnu
SUFFIX_LFLAGS=-lmysqlcppconn

all: StoreCSV2SQL

StoreCSV2SQL: StoreCSV2SQL.o
	$(CC) $(LFLAGS) StoreCSV2SQL.o -o StoreCSV2SQL.elf $(SUFFIX_LFLAGS)

StoreCSV2SQL.o: StoreCSV2SQL.cpp
	$(CC) $(CFLAGS) StoreCSV2SQL.cpp -o StoreCSV2SQL.o

clean:
	rm *.o StoreCSV2SQL.elf
