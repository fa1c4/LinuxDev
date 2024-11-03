CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lcrypto -lssl

all: digest_disp digest_file digest_verify

digest_disp: digest_disp.o
	$(CC) digest_disp.o -o digest_disp.elf $(LDFLAGS)
digest_disp.o: digest_disp.cpp
	$(CC) $(CFLAGS) digest_disp.cpp -o digest_disp.o

digest_file: digest_file.o
	$(CC) digest_file.o -o digest_file.elf $(LDFLAGS)
digest_file.o: digest_file.cpp
	$(CC) $(CFLAGS) digest_file.cpp -o digest_file.o

digest_verify: digest_verify.o
	$(CC) digest_verify.o -o digest_verify.elf $(LDFLAGS)
digest_verify.o: digest_verify.cpp
	$(CC) $(CFLAGS) digest_verify.cpp -o digest_verify.o

clean:
	rm *.o *.elf
	