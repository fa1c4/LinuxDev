# make file for WebForm

CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lm -lcgicc

all: WebForm

WebForm: WebForm.o mWebAppGet.o
	$(CC) WebForm.o -o WebForm.elf $(LDFLAGS)
	$(CC) mWebAppGet.o -o mWebAppGet.elf $(LDFLAGS)

WebForm.o: WebForm.cpp mWebAppGet.cpp
	$(CC) $(CFLAGS) WebForm.cpp -o WebForm.o $(LDFLAGS)
	$(CC) $(CFLAGS) mWebAppGet.cpp -o mWebAppGet.o $(LDFLAGS)

install:
	sudo cp WebForm.elf /var/www/html/cgi-enabled/WebForm.cgi
	sudo cp mWebAppGet.elf /var/www/html/cgi-enabled/mWebAppGet.cgi

uninstall:
	sudo rm -f /var/www/html/cgi-enabled/WebForm.cgi
	sudo rm -f /var/www/html/cgi-enabled/mWebAppGet.cgi

clean:
	rm *.o *.elf
	