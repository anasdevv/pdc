#!/bin/bash

mpicc task3_a.c -o t3a
mpicc task3_b.c -o t3b
mpicc task3_c.c -o t3c
mpicc task5.c -o t5
mpicc task4.c -o t4

# Define an array of  sizes
message_sizes=(10000 20000 30000 40000 50000 60000 70000 80000 90000 100000)
procs_sizes=(2 4 6)
arr_sizes=(100 200 300 400 500)
# for size in "${message_sizes[@]}"; do
#     echo "Testing with message size: $size"
    
#     # Run the programs and measure execution time
#     blocking_time=$(mpirun -np 2 ./t3a $size)
#     nonblocking_time=$(mpirun -np 2 ./t3b $size)
#     sendrecv_time=$(mpirun -np 2 ./t3c $size)
    
# done


# for proc in "${procs_sizes[@]}"; do
#     echo "Testing with number of processes: $proc"
    
#     # Run the programs and measure execution time
#     blocking_time=$(mpirun --oversubscribe -np $proc ./t5 50)
#     nonblocking_time=$(mpirun --oversubscribe -np $proc ./t5 50)
#     sendrecv_time=$(mpirun --oversubscribe -np $proc ./t5 50)  
    
#     blocking_time=$(mpirun --oversubscribe -np $proc ./t5 100)
#     nonblocking_time=$(mpirun --oversubscribe -np $proc ./t5 100)
#     sendrecv_time=$(mpirun --oversubscribe -np $proc ./t5 100)
    
# done

for arr_size in "${arr_sizes[@]}"; do
    echo "Testing with number of processes: $proc"
    
        # Run the programs and measure execution time
    blocking_time=$(mpirun --oversubscribe -np 2 ./t4 $arr_size)
    
done