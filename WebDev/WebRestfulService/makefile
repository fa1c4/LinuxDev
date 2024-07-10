CC=g++
CFLAGS=-c -Wall -Werror -g -I/usr/include/mongocxx -I/usr/include/bsoncxx
LDFLAGS=-lm -lrestbed -L/usr/lib/x86_64-linux-gnu -lmongocxx -lbsoncxx --std=c++17


# all: myWebServiceGet myWebServiceGetParam
all: mWebServiceGet

mWebServiceGet: mWebServiceGet.o
	$(CC) mWebServiceGet.o -o mWebServiceGet.elf $(LDFLAGS)
mWebServiceGet.o: mWebServiceGet.cpp
	$(CC) $(CFLAGS) mWebServiceGet.cpp

mWebServiceGetParam: mWebServiceGetParam.o
	$(CC) mWebServiceGetParam.o -o mWebServiceGetParam.elf $(LDFLAGS)
mWebServiceGetParam.o: mWebServiceGetParam.cpp
	$(CC) $(CFLAGS) mWebServiceGetParam.cpp

clean:
	rm *.o *.elf
