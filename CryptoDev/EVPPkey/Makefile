CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lcrypto -lssl -lrt -lpthread -lboost_system

all: evp_readkey_file evp_generate_rsakey pkey_sending pkey_recving

evp_generate_rsakey: evp_generate_rsakey.o evp_class.o
	$(CC) evp_generate_rsakey.o evp_class.o -o evp_generate_rsakey.elf $(LDFLAGS)
evp_generate_rsakey.o: evp_generate_rsakey.cpp
	$(CC) $(CFLAGS) evp_generate_rsakey.cpp -o evp_generate_rsakey.o

evp_readkey_file: evp_readkey_file.o evp_class.o
	$(CC) evp_readkey_file.o evp_class.o -o evp_readkey_file.elf $(LDFLAGS)
evp_readkey_file.o: evp_readkey_file.cpp
	$(CC) $(CFLAGS) evp_readkey_file.cpp -o evp_readkey_file.o

pkey_sending: pkey_sending.o evp_class.o
	$(CC) pkey_sending.o evp_class.o -o pkey_sending.elf $(LDFLAGS)
pkey_sending.o: pkey_sending.cpp
	$(CC) $(CFLAGS) pkey_sending.cpp -o pkey_sending.o

pkey_recving: pkey_recving.o evp_class.o
	$(CC) pkey_recving.o evp_class.o -o pkey_recving.elf $(LDFLAGS)
pkey_recving.o: pkey_recving.cpp
	$(CC) $(CFLAGS) pkey_recving.cpp -o pkey_recving.o

evp_class.o: evp_class.cpp
	$(CC) $(CFLAGS) evp_class.cpp -o evp_class.o

clean:
	rm *.o *.elf
