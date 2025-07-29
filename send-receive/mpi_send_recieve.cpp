#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Say we are sending and receiving in the same program then to distinguish the processes we use the rank
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // We know how many processes can be handled so accordingly we do the things.
    // But when user is handling the product we give, then he doesn't know regarding how many processes can be there
    // In that case, we need to handle such that it doesn't throw an error

    // Handle the case where there are fewer than 2 processes
    if (world_size < 2) {
        std::cerr << "This program requires at least two processes." <<std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    int TAG = 0;
    int message;
    // NOTE: This should not be initialized over here, it has to be only declared over here because 
    // in case of sending only we need the buffer with data and 
    // in case of receiving we need an empty buffer

    if (world_rank == 0) {
        // Prepare a message to send (initialization done in this scope)
        message = 10;

        // MPI_Send(buffer, count, MPI_Datatype, dest, tag, comm)
        MPI_Send(&message, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);

        // &message -> address of the buffer (buffer is used to stream the message)
        // 1        -> only one integer which is 10 in this case
        // MPI_INT  -> 
        // 1        -> destination rank is 1 because the current rank is 0
        // TAG      -> when there are multiple pieces of data, the msgs will not be received in order, 
        //             to ensure the same order while receiving we use tags
        // MPI_COMM_WORLD   -> default communicator here

        std::cout<<"Process "<<world_rank<<": Sent message: "<<message<<std::endl;
    } else if (world_rank == 1) {
        //MPI_Recv(buffer, count, MPI_Datatype, source, tag, comm, status)
        MPI_Recv(&message, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // count    -> this should be at least equal as in case of sending
        // status   -> we can define one more buffer to store this status
        //             the status buffer can contain the metadata about the message which is been sent

        std::cout<<"Process "<<world_rank<<": Received message: "<<message<<std::endl;
    }

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}