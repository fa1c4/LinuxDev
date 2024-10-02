// mpirun --oversubscribe -np 8 mpi_scatter.elf
#include <boost/mpi.hpp>
#include <boost/mpi/collectives.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

namespace mpi = boost::mpi;


int main(int argc, char* argv[]) {
    mpi::environment env(argc, argv);
    mpi::communicator comm;

    std::vector<int> mVec;
    int outVal = -1;

    if (comm.rank() == 0) {
        for (int i = 0; i < comm.size(); ++i) {
            int mVal = i * comm.size();
            mVec.push_back(mVal);
            std::cout << "Rank: " << comm.rank() << " mVec(" << i << ") = " << mVal << std::endl;
        }
    }

    mpi::scatter(comm, mVec, outVal, 0);
    for (int r = 0; r < comm.size(); ++r) {
        comm.barrier();
        if (r == comm.rank()) {
            std::cout << "Rank " << r << " got " << outVal << std::endl;
        }
    }

    return 0;
}
