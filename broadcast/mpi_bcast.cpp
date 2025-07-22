#include <iostream>
#include <mpi.h>

// Use mpich.org -> references

int main(int argc, char** argv) {
    // Initialize MPI Environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Prepare data to be broadcasted
    int data;
    if (world_rank == 0) {
        data = 42;  // Root initializes the data
    } else {
        data = 0;   // Other processes will receive this value
    }
    
    // Broadcasting of data means a collection of data is passed synchronously
    // Broadcast the data from the root process (rank 0) to all other processes
    // MPI_Bcast(buffer, count, MPI_Datatype, root, communicator)
    // This is given outside the "if" statement because it is common to all processes and acts different for each process
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each processes prints the received data
    std::cout<<"Process "<<world_rank<<": Received data: "<<data<<std::endl;

    // Finalize MPI Environment
    MPI_Finalize();
    return 0;
}