#include <mpi.h>
#include <iostream>


int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int val_sent = 17;
        int result = MPI_Send(&val_sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        if (result == MPI_SUCCESS)
            std::cout << "Rank 0 Send " << val_sent << " to Rank 1 tag 0" << std::endl;
    } else if (rank == 1) {
        int val_rcv;
        int result = MPI_Recv(&val_rcv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (result == MPI_SUCCESS)
            std::cout << "Rank 1 Rcvd " << val_rcv << " from Rank 0 tag 0" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
