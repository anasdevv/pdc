#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

/*
Task#5: Write a program in MPI C to generate factorial up to 50 and 100 terms. Measure
the performance (execution time) of the code for 2, 4, and 6 MPI processes and plot it
on excel.
*/

unsigned long long int calculate_factorial(int n) {
    unsigned long long int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int num_terms = 50;  
    FILE *file = fopen("factorial_execution_times.csv", "a");
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc == 2) {
        num_terms = atoi(argv[1]);
    }

    double start_time, end_time;
    unsigned long long int local_results[num_terms];
    unsigned long long int global_results[num_terms];

    for (int i = 0; i < num_terms; i++) {
        local_results[i] = 0;
        global_results[i] = 0;
    }

    if (rank == 0) {
        printf("Calculating factorials up to %d terms with %d MPI processes\n", num_terms, size);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    for (int i = rank; i < num_terms; i += size) {
        local_results[i] = calculate_factorial(i + 1);
    }

    MPI_Allreduce(local_results, global_results, num_terms, MPI_UNSIGNED_LONG_LONG, MPI_MAX, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Factorials of %d terms:\n", num_terms);
        for (int i = 0; i < num_terms; i++) {
            printf("%d! = %llu\n", i + 1, global_results[i]);
        }
        printf("Time taken: %lf seconds\n", end_time - start_time);
    }

    MPI_Finalize();

    // Output execution time to a file for analysis in Excel
    if (rank == 0) {
        fprintf(file, "%d, %d, %lf\n", num_terms, size, end_time - start_time);
        fclose(file);
    }

    return 0;
}
