# makefile for test Java Native Interface
# javac -h . TestJNI.java to build jni header first
# then make the so lib

JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
CC=g++
CFLAGS=-c -Wall -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -I./
LDFLAGS=-shared -L${JAVA_HOME}/lib

all: libJNItest.so

libJNItest.so: libJNItest.o
	$(CC) libJNItest.o -o libJNItest.so $(LDFLAGS)

libJNItest.o: libJNItest.cpp
	$(CC) $(CFLAGS) libJNItest.cpp -o libJNItest.o

clean:
	rm *.o libJNItest.so

run:
	java -Djava.library.path=. TestJNI
