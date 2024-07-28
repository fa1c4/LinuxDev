# makefile for PDFlab

CC=g++
CLFAGS=-c -Wall -g -I.
LFLAGS=-lm

all: pdfDump

pdfDump: pdfDump.o
	$(CC) pdfDump.o -o pdfDump.elf $(LFLAGS)

pdfDump.o: pdfDump.cpp
	$(CC) $(CLFAGS) pdfDump.cpp -o pdfDump.o

clean:
	rm *.o *.elf *.txt
