// mpirun --oversubscribe -np 8 mpi_gather.elf
#include <boost/mpi.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

namespace mpi = boost::mpi;


int main(int argc, char* argv[]) {
    mpi::environment env;
    mpi::communicator comm;

    if (comm.rank() == 0) {
        std::vector<int> mVec;
        int inVal = comm.rank() * comm.size();
        std::cout << "Rank: " << comm.rank() << " value " << inVal << std::endl;

        gather(comm, inVal, mVec, 0);
        for (int proc = 0; proc < comm.size(); ++proc) {
            std::cout << "Rank: " << comm.size() << " mVec(" << proc << ") = " << mVec[proc] << std::endl;
        }
    } else {
        int inVal = comm.rank() * comm.size();
        std::cout << "Rank: " << comm.rank() << " value: " << inVal << std::endl;
        gather(comm, inVal, 0);
    }

    return 0;
}
