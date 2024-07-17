# makefile for object library

# executes the commands below to make library.so and mObjTest.elf
# make clean
# make mSquare.[s]o
# make mTriangle.[s]o
# make

# <bug> for thers commands
# g++ --share -Wl,-soname,libAreaLib.so.1 -o libAreaLib.so.1.0 *.o
# ln -sf libAreaLib.so.1.0 libAreaLib.so.1
# ln -sf libAreaLib.so.1.0 libAreaLib.so

# no need for these commands
# export LD_LIBRARY_PATH=.
# or
# sudo cp libAreaLib.so* /usr/local/lib/

CC=g++
CFLAGS=-c -Wall -I.
LDFLAGS=-lm -L. -lmSquare -lmTriangle

OBJ_LIST=mObjTest.o mSquare.o mTriangle.o

all: mObjTest

# original make
# mObjTest: $(OBJ_LIST)
# 	$(CC) $(LDFLAGS) $(OBJ_LIST) -o mObjTest.elf

# link library make
mObjTest: mObjTest.o
	$(CC) $(LDFLAGS) mObjTest.o -o mObjTest.elf

mObjTest.o: mObjTest.cpp
	$(CC) $(CFLAGS) mObjTest.cpp -o mObjTest.o

mSquare.so: mSquare.cpp
	$(CC) $(CFLAGS) -fPIC mSquare.cpp -o libmSquare.so

mTriangle.so: mTriangle.cpp
	$(CC) $(CFLAGS) -fPIC mTriangle.cpp -o libmTriangle.so

clean:
	rm *.o *.elf 

clean_so:
	rm *.so
