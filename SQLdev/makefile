# Makefile lab for TestConnSQL

CC=g++
CFLAGS=-c -Wall -I/usr/include/cppconn
LFLAGS=-lm -L/usr/lib/x86_64-linux-gnu
SUFFIX_LFLAGS=-lmysqlcppconn

all: TestConnSQL

TestConnSQL: TestConnSQL.o
	$(CC) $(LFLAGS) TestConnSQL.o -o TestConnSQL.elf $(SUFFIX_LFLAGS)

TestConnSQL.o: TestConnSQL.cpp
	$(CC) $(CFLAGS) TestConnSQL.cpp -o TestConnSQL.o

clean:
	rm *.o TestConnSQL.elf
