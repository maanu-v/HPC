#include <iostream>
#include <mpi.h>

// For compiling this code
//      mpic++ ./<filename> -o <output_file_name>
// For running the code
//      mpirun -np <no_of_processes> <output_file_name>
// In the hostfile, we have slots which can be said as max no of processes
// To run using hostfile
//      mpirun -np <no_of_processes> --hostfile hostfile <output_file_dir>
int main(int argc, char *argv[])
{
    // Initialize the MPI environment
    // Here to each core/processors we have to pass the memory because it has no shared memory
    MPI_Init(&argc, &argv);

    // Get the number of processes
    // Each core can run 1 process at a time but lets take lap which has a processor which consists of cores
    // In that case we can parallely open many apps right which is a process too
    // The OS Scheduler comes handy here.. coz our human time is long.. the system is too fast..
    // Each process is scheduled in such a way that all the processes are running parallelly
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of world
    // If we have n processes then rank of the processes varies from 0 to n-1
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // We have to print hello world from all the processes and also find the rank of each process
    std::cout << "Hello world from process " << world_rank << " of " << world_size << std::endl;

    // Say we have 4 processors and 4 processes then there are no issues
    // If we have 4 processors and 10 processes then we have to use oversubscribe the processors
    MPI_Finalize();
    return 0;
}