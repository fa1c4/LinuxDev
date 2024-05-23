# Makefile lab for ParallRead

CC=g++
CFLAGS=-c -Wall
LFLAGS=-lm -pthread -std=c++11

all: ParallRead

ParallRead: ParallRead.o
	$(CC) $(LFLAGS) ParallRead.o -o ParallRead

ParallRead.o: ParallRead.cpp
	$(CC) $(CFLAGS) ParallRead.cpp -o ParallRead.o

clean:
	rm *.o ParallRead

# make for LabRead
# all: LabRead
# 
# LabRead: LabRead.o
# 	$(CC) $(LFLAGS) LabRead.o -o LabRead
# 
# LabRead.o: LabRead.cpp
# 	$(CC) $(CFLAGS) LabRead.cpp -o LabRead.o
# 
# clean:
# 	rm *.o LabRead
