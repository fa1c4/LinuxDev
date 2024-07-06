# make file for WebTesting

CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lm

all: WebTesting

WebTesting: WebTesting.o
	$(CC) WebTesting.o -o WebTesting.elf $(LDFLAGS)

WebTesting.o: WebTesting.cpp
	$(CC) $(CFLAGS) WebTesting.cpp -o WebTesting.o $(LDFLAGS)

install:
	sudo cp WebTesting.elf /var/www/html/cgi-enabled/WebTesting.cgi

uninstall:
	sudo rm -f /var/www/html/cgi-enabled/WebTesting.cgi

clean:
	rm *.o WebTesting.elf
	