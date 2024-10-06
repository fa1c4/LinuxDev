# makefile for OpenSSL BIO demo

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lcrypto -lssl

all: bio_file bio_b64enc bio_b64dec

bio_file: bio_file.o
	$(CC) bio_file.o -o bio_file.elf $(LDFLAGS)
bio_file.o: bio_file.cpp
	$(CC) $(CFLAGS) bio_file.cpp -o bio_file.o

bio_b64enc: bio_b64enc.o
	$(CC) bio_b64enc.o -o bio_b64enc.elf $(LDFLAGS)
bio_b64enc.o: bio_b64enc.cpp
	$(CC) $(CFLAGS) bio_b64enc.cpp -o bio_b64enc.o

bio_b64dec: bio_b64dec.o
	$(CC) bio_b64dec.o -o bio_b64dec.elf $(LDFLAGS)
bio_b64dec.o: bio_b64dec.cpp
	$(CC) $(CFLAGS) bio_b64dec.cpp -o bio_b64dec.o

clean:
	rm *.o *.elf
	