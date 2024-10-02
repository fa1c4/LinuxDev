// mpirun --oversubscribe -np 8 mpi_reduce.elf
#include <boost/mpi.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

namespace mpi = boost::mpi;


int main(int argc, char* argv[]) {
    mpi::environment env;
    mpi::communicator comm;
    int mVal = 0;

    if (comm.rank() == 0) {
        int totVal = 0;
        mVal = comm.rank() * comm.size();
        std::cout << "Rank: " << comm.rank() << " Value = " << mVal << std::endl;
        reduce(comm, mVal, totVal, std::plus<int>(), 0);
        std::cout << "Rank: " << comm.rank() << " total value = " << totVal << std::endl;
    } else {
        mVal = comm.rank() * comm.size();
        std::cout << "Rank: " << comm.rank() << " Value = " << mVal << std::endl;
        reduce(comm, mVal, std::plus<int>(), 0);
    }

    return 0;
}
