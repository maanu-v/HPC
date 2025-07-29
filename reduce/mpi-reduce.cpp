// A simple program to demonstrate MPI Reduce operation with local errors computed as sum of least squares ibto a global error variable

#include <iostream>
#include <mpi.h>
#include <cmath>

int main(int argc, char **argv)
{
    // Initialise the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // 1. Each process computes its local error
    double local_error = world_rank + 1; // Example: local error is simply the rank + 1
    double local_error_squared = local_error * local_error;

    // 2. Reduce operation to compute the global error as the sum of local errors squared
    double global_error_squared;
    // MPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, communicator)
    MPI_Reduce(&local_error_squared, &global_error_squared, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // 3. The root process (rank 0) will print the global error
    if (world_rank == 0)
    {
        double global_error = std::sqrt(global_error_squared); // Compute the square root to get the global error
        std::cout << "Global error (sum of local errors squared/ least squares): "
                  << global_error << std::endl;
    }

    // Finalise the MPI environment
    MPI_Finalize();
    return 0;
}