CC=g++
CFLAGS=-c -Werror -g -I/usr/include/mongocxx -I/usr/include/bsoncxx
# LDFLAGS=-lcurl -lboost_json -lpthread -lboost_system -lrestbed -lmongocxx -lbsoncxx --std=c++17
LDFLAGS=-lcurl -lpthread -lboost_system -lrestbed -lmongocxx -lbsoncxx --std=c++17

all: EchoGetPostWS libcurl_httpget libcurl_httppost

EchoGetPostWS: EchoGetPostWS.o
	$(CC) EchoGetPostWS.o -o EchoGetPostWS.elf $(LDFLAGS)
EchoGetPostWS.o: EchoGetPostWS.cpp
	$(CC) $(CFLAGS) EchoGetPostWS.cpp -o EchoGetPostWS.o

libcurl_httpget: libcurl_httpget.o
	$(CC) libcurl_httpget.o -o libcurl_httpget.elf $(LDFLAGS)
libcurl_httpget.o: libcurl_httpget.cpp
	$(CC) $(CFLAGS) libcurl_httpget.cpp -o libcurl_httpget.o

libcurl_httppost: libcurl_httppost.o
	$(CC) libcurl_httppost.o -o libcurl_httppost.elf $(LDFLAGS)
libcurl_httppost.o: libcurl_httppost.cpp
	$(CC) $(CFLAGS) libcurl_httppost.cpp -o libcurl_httppost.o

clean: 
	rm *.o *.elf
