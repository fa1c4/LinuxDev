# makefile for mQueue demo
# notice: sudo ./mQueue*.elf to create /dev/mqueue/xxxqueue directory

GXX=g++
CFLAGS=-c -Wall -g
LFLAGS=-lpthread -lrt

all: mQueueSend mQueueRecv mQueueNotice

mQueueSend: mQueueSend.o
	$(GXX) mQueueSend.o -o mQueueSend.elf $(LFLAGS)

mQueueSend.o: mQueueSend.cpp
	$(GXX) $(CFLAGS) mQueueSend.cpp -o mQueueSend.o

mQueueRecv: mQueueRecv.o
	$(GXX) mQueueRecv.o -o mQueueRecv.elf $(LFLAGS)

mQueueRecv.o: mQueueRecv.cpp
	$(GXX) $(CFLAGS) mQueueRecv.cpp -o mQueueRecv.o

mQueueNotice: mQueueNotice.o
	$(GXX) mQueueNotice.o -o mQueueNotice.elf $(LFLAGS)

mQueueNotice.o: mQueueNotice.cpp
	$(GXX) $(CFLAGS) mQueueNotice.cpp -o mQueueNotice.o

clean:
	rm *.o *.elf
