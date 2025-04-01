#include <stdio.h>
#include <omp.h>

int main(void) {
    int i;

    // -------------------------------
    // Parallel Loop using OpenMP parallel for
    // -------------------------------
    omp_set_num_threads(4); // Set the number of threads to 4
    printf("Program start : Using %d threads\n\n\n", omp_get_max_threads());

    double start_parallel_for = omp_get_wtime();
    
    #pragma omp parallel for private(i)
    for (i = 0; i <= 50; i++) {
        printf("Parallel for - Thread %d: Iteration %d\n", omp_get_thread_num(), i);
    }
    
    double end_parallel_for = omp_get_wtime();
    printf("Total parallel for time: %f seconds\n\n", end_parallel_for - start_parallel_for);


    // -------------------------------
    // Parallel Tasks using explicit tasks (4 tasks)
    // -------------------------------
    double start_tasks = omp_get_wtime();
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            // Task 1: iterations 0 to 12
            #pragma omp task
            {
                for (int j = 0; j <= 12; j++) {
                    printf("Task 1 - Thread %d: Iteration %d\n", omp_get_thread_num(), j);
                }
            }
            // Task 2: iterations 13 to 25
            #pragma omp task
            {
                for (int j = 13; j <= 25; j++) {
                    printf("Task 2 - Thread %d: Iteration %d\n", omp_get_thread_num(), j);
                }
            }
            // Task 3: iterations 26 to 37
            #pragma omp task
            {
                for (int j = 26; j <= 37; j++) {
                    printf("Task 3 - Thread %d: Iteration %d\n", omp_get_thread_num(), j);
                }
            }
            // Task 4: iterations 38 to 50
            #pragma omp task
            {
                for (int j = 38; j <= 50; j++) {
                    printf("Task 4 - Thread %d: Iteration %d\n", omp_get_thread_num(), j);
                }
            }
            // We could have automated the loop separation on 50, but this is just for demonstration.
            // The single construct will wait for all tasks to complete before exiting the block.
        }
    }
    
    double end_tasks = omp_get_wtime();
    printf("Total explicit tasks time: %f seconds\n\n", end_tasks - start_tasks);

    // -------------------------------
    // Serial Loop for reference
    // -------------------------------
    double start_serial = omp_get_wtime();
    
    for (i = 0; i <= 50; i++) {
        printf("Serial: Iteration %d\n", i);
    }
    
    double end_serial = omp_get_wtime();
    printf("Total serial time: %f seconds\n", end_serial - start_serial);

    return 0;
}
