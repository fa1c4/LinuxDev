# makefile for Integrate Cpp and Python
# notice that there is no need -lpython | -lpython3 | -lpython38

CC=g++
CFLAGS=-c -Wall -fPIC -I/usr/include/python3.8 -I/usr/include/boost
LDFLAGS=-shared -export-dynamic -lboost_python38 -L/usr/lib/python3.8/config-3.8-x86_64-linux-gnu

all: pCpplib.so

pCpplib.so: pCpplib.o
	$(CC) pCpplib.o -o pCpplib.so $(LDFLAGS)
pCpplib.o: pCpplib.cpp
	$(CC) $(CFLAGS) pCpplib.cpp -o pCpplib.o

clean:
	rm *.o *.so
