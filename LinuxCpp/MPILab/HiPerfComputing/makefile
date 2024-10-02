# makefile for High Performance Computing demo
# sudo apt-get install libboost-all-dev to install lboost_mpi
# use lboost_serialization instead of lboost_serialization_67
# install mpi-4.xx

CXX=g++
MPI_CXX=mpic++
CFLAGS=-c -Wall -g -I/usr/local/include/boost/mpi
LDFLAGS=-L/usr/local/lib -lboost_mpi -lboost_serialization

all: mpi_gather mpi_scatter mpi_reduce

mpi_gather: mpi_gather.o
	$(MPI_CXX) mpi_gather.o -o mpi_gather.elf $(LDFLAGS)
mpi_gather.o: mpi_gather.cpp
	$(CXX) $(CFLAGS) mpi_gather.cpp -o mpi_gather.o

mpi_scatter: mpi_scatter.o
	$(MPI_CXX) mpi_scatter.o -o mpi_scatter.elf $(LDFLAGS)
mpi_scatter.o: mpi_scatter.cpp
	$(CXX) $(CFLAGS) mpi_scatter.cpp -o mpi_scatter.o

mpi_reduce: mpi_reduce.o
	$(MPI_CXX) mpi_reduce.o -o mpi_reduce.elf $(LDFLAGS)
mpi_reduce.o: mpi_reduce.cpp
	$(CXX) $(CFLAGS) mpi_reduce.cpp -o mpi_reduce.o

clean:
	rm *.o *.elf
