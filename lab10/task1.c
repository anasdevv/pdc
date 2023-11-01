#include<stdio.h>
#include<mpi.h>
// Task#1: Convert the hello world program to print its messages in rank order.

int main(){
    int rank, size;
    MPI_Init(NULL ,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for(int i = 0; i < size; i++){
        if(rank == i){
            printf("Hello world from process %d of %d\n", rank, size);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
