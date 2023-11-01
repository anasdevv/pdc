#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


// coarse grained
// as task is divided into large chunks of small number of problems
void oddEvenSort(int *arr, int n)
{
    int sorted = 0;
    int phase, temp;
    for (phase = 0; phase < n; phase++)
    {
        if (phase % 2 == 0)
        {
            for (int i = 1; i < n; i += 2)
            {
                if (arr[i - 1] > arr[i])
                {
                    temp = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = temp;
                }
            }
        }
        else
        {
            for (int i = 1; i < n - 1; i += 2)
            {
                if (arr[i] > arr[i + 1])
                {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        }
    }
}
int main(int argc, char **argv)
{
            FILE *file = fopen("evenOdd_t4.csv", "a");

    MPI_Init(NULL,NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n = 10; // Change this to the desired array size
     if (argc == 2)
    {
        n = atoi(argv[1]);
        printf("Size of array: %d\n", n);
    }
    int *arr = (int *)malloc(n * sizeof(int));
    double start_time = MPI_Wtime();
    if (rank == 0)
    {
        // Initialize the array with random values on the root process
        printf("Original Array: ");
        srand(123); // Seed for random number generation
        for (int i = 0; i < n; i++)
        {

            arr[i] = rand() % 100;
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    // Broadcast the array to all processes
    MPI_Bcast(arr, n, MPI_INT, 0, MPI_COMM_WORLD);
    // Perform parallel odd-even sort
    oddEvenSort(arr, n);
    // Gather the sorted portions back to the root process
    int *sortedArr = NULL;
    if (rank == 0)
    {
        sortedArr = (int *)malloc(n * sizeof(int));
    }
    MPI_Gather(arr, n, MPI_INT, sortedArr, n, MPI_INT, 0, MPI_COMM_WORLD);
    // Print the sorted array on the root process
    if (rank == 0)
    {
        double end_time = MPI_Wtime();
        printf("Sorted Array: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", sortedArr[i]);
        }
        printf("\n");
        fprintf(file, "%d %lf\n", n, end_time - start_time);
        printf("Time taken: %lf\n", end_time - start_time);
        free(sortedArr);
    }
    free(arr);
    MPI_Finalize();
    return 0;
}