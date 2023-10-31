#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define n 5
/*

This MPI (Message Passing Interface) example demonstrates the use of broadcast,
 calculation, and communication in a distributed computing environment. 
 The program consists of multiple processes, each with a unique rank, 
 communicating and performing calculations on shared data.
  It's important to note that this code illustrates a common source of confusion for
   individuals new to MPI, emphasizing that MPI_Recv() is not used to receive data 
   sent by a broadcast; 
  MPI_Bcast() is the appropriate method for this purpose.

*/
/*
process 1 cacluates Product of Array Except Self
Given an integer array nums, return an array answer such that answer[i] 
is equal to the product of all the elements of nums except nums[i].
note : this solution exists only for non zero entries

process 2 calculates Sum of Array Except Self
Given an integer array nums, return an array answer such that answer[i] 
is equal to the sum of all the elements of nums except nums[i].
*/


int main()
{
    int rank, size;
    int data[n];
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
            data[i] = i+1;
        MPI_Bcast(data, n, MPI_INT, 0, MPI_COMM_WORLD);
    }
    if (rank == 1)
    {
        int local_data[n];
        int local_product = 1;
        float local_div[n];
        MPI_Bcast(local_data, n, MPI_INT, 0, MPI_COMM_WORLD);
        for (int i = 0; i < n; i++)
        {
            local_product *= local_data[i];
        }
        for (int i = 0; i < n; i++)
        {
            local_div[i] = local_product / local_data[i];
        }
        MPI_Send(local_div, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    if (rank == 2)
    {
        int local_data[n];
        int local_sum = 0;
        MPI_Bcast(local_data, n, MPI_INT, 0, MPI_COMM_WORLD);
        for (int i = 0; i < n; i++)
        {
            local_sum += local_data[i];
        }
        for (int i = 0; i < n; i++)
        {
            local_data[i] = local_sum - local_data[i];
        }
        MPI_Send(local_data, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0)
    {
        int received_sum[n];
        float received_product[n];
        MPI_Recv(&received_product, n, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nReceived product result\n");
        for (int i = 0; i < n; i++)
        {
            printf("Received product result: %f.2f\n", received_product[i]);
        }

        MPI_Recv(&received_sum, n, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nReceived product result\n");
        for (int i = 0; i < n; i++)
        {
            printf("Received sum result: %d\n", received_sum[i]);
        }
    }

    MPI_Finalize();
    return 0;
}