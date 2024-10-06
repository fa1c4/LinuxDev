# makefile for EVP Interface

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lcrypto -lssl

all: evp_display evp_encrypt evp_decrypt

evp_display: evp_display.o evp_class.o
	$(CC) evp_display.o evp_class.o -o evp_display.elf $(LDFLAGS)
evp_display.o: evp_display.cpp
	$(CC) $(CFLAGS) evp_display.cpp -o evp_display.o

evp_encrypt: evp_encrypt.o evp_class.o
	$(CC) evp_encrypt.o evp_class.o -o evp_encrypt.elf $(LDFLAGS)
evp_encrypt.o: evp_encrypt.cpp
	$(CC) $(CFLAGS) evp_encrypt.cpp -o evp_encrypt.o

evp_decrypt: evp_decrypt.o evp_class.o
	$(CC) evp_decrypt.o evp_class.o -o evp_decrypt.elf $(LDFLAGS)
evp_decrypt.o: evp_decrypt.cpp
	$(CC) $(CFLAGS) evp_decrypt.cpp -o evp_decrypt.o

evp_class.o: evp_class.cpp
	$(CC) $(CFLAGS) evp_class.cpp -o evp_class.o

clean:
	rm *.o *.elf
