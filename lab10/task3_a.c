#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
/*
Task#3: Write two programs in MPI C and measure their time using MPI_Wtime.
a) Use blocking send and receive an array of 10,000 elements
*/
int main(int argc , char *argv[]){

    int rank, size;
     int arr_size = 10000;
    FILE *file = fopen("blocking_send_recv_3a.csv", "a");
    if(argc == 2){
        arr_size = atoi(argv[1]);
    }
    int arr[arr_size];
    MPI_Init(NULL, NULL);
    double start_time, end_time;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0 ){
        for(int i = 0 ; i < arr_size ; i++){
            arr[i] = rand();
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0){
        start_time = MPI_Wtime();
        MPI_Send(arr, arr_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    if(rank == 1 ){
        MPI_Recv(arr, arr_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
     MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0 ){
        printf("Size of array: %d\n", arr_size);
         end_time = MPI_Wtime();
         printf("Time taken: %lf\n", end_time - start_time);
            fprintf(file, "%d %lf\n", arr_size, end_time - start_time);

    }
    MPI_Finalize();
    return 0;
}