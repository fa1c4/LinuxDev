# makefile for PDFlab

CC=g++
CLFAGS=-c -Wall -g -I.
LFLAGS=-lm

all: pdfDump pdfCountPages

pdfDump: pdfDump.o
	$(CC) pdfDump.o -o pdfDump.elf $(LFLAGS)

pdfDump.o: pdfDump.cpp
	$(CC) $(CLFAGS) pdfDump.cpp -o pdfDump.o

pdfCountPages: pdfCountPages.o
	$(CC) pdfCountPages.o -o pdfCountPages.elf $(LFLAGS)

pdfCountPages.o: pdfCountPages.cpp
	$(CC) $(CLFAGS) pdfCountPages.cpp -o pdfCountPages.o

clean:
	rm *.o *.elf *.txt
