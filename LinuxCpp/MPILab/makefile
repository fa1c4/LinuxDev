# makefile for MPI test

CXX=g++
MPI_CXX=mpic++
CFLAGS=-c -Wall -g

all: mpi_test mpi_version

mpi_test: mpi_test.o
	$(MPI_CXX) mpi_test.o -o mpi_test.elf
mpi_test.o: mpi_test.cpp
	$(CXX) $(CFLAGS) mpi_test.cpp -o mpi_test.o

mpi_version: mpi_version.o
	$(MPI_CXX) mpi_version.o -o mpi_version.elf
mpi_version.o: mpi_version.cpp
	$(CXX) $(CFLAGS) mpi_version.cpp -o mpi_version.o

clean:
	rm *.o *.elf
	