#include <stdio.h>
#include <mpi.h>

/*
Task#2: Write two programs in MPI C where process with rank zero sends a message and
a process with rank 1 receives a message with a tag=your student id. (Hint: Lab#6)
b) Use Non-Blocking send receive and measure the time MPI_Wtime
*/
int main()
{
    int rank, size;
    const int tag = 3437;
    MPI_Init(NULL, NULL);
    char msg[] = "Hello world\0";
    double start_time, end_time;
    MPI_Request send_request, recv_request;
    const int msg_size = sizeof(msg);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        printf("Process with rank %d sending message to process with rank 1\n", rank);
        start_time = MPI_Wtime();
        MPI_Isend(msg, msg_size, MPI_CHAR, 1, tag, MPI_COMM_WORLD , &send_request);
        MPI_Wait(&send_request, MPI_STATUS_IGNORE);

    }

    if (rank == 1)
    {
        char received_msg[msg_size];
        MPI_Irecv(received_msg, msg_size, MPI_CHAR, 0, tag, MPI_COMM_WORLD , &recv_request);
         MPI_Wait(&recv_request, MPI_STATUS_IGNORE);
        printf("Process with rank %d received message: %s\n", rank, received_msg);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0 ){
         end_time = MPI_Wtime();
         printf("Time taken: %lf\n", end_time - start_time);

    }
    MPI_Finalize();

    return 0;
}
