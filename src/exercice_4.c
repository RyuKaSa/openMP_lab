#include <stdio.h>
#include <omp.h>

int main(void)
{
    static long nb_pas = 1000000000;
    double pas = 1.0 / (double)nb_pas;
    double x, pi, som;
    int i, iter;
    double start, end;
    double total_time = 0.0;

    // Loop over different thread counts from 1 to 16
    for (int thread_num = 1; thread_num <= 16; thread_num++)
    {
        omp_set_num_threads(thread_num);
        total_time = 0.0;
        printf("Using %d threads:\n", thread_num);

        // Run 10 iterations to compute PI and measure time
        for (iter = 1; iter <= 10; iter++)
        {
            som = 0.0;
            start = omp_get_wtime();
            
            // Parallelized loop using the current thread count
            // #pragma omp parallel for private(x) reduction(+:som)
            #pragma omp parallel for schedule(static) private(x) reduction(+:som)
            // #pragma omp parallel for schedule(dynamic) private(x) reduction(+:som)
            for (i = 0; i < nb_pas; i++)
            {
                x = (i + 0.5) * pas;
                som += 4.0 / (1.0 + x * x);
            }
            
            end = omp_get_wtime();
            pi = pas * som;
            double elapsed = end - start;
            total_time += elapsed;
            // printf("  Iteration %d: PI = %2.15f, time = %f seconds\n", iter, pi, elapsed);
        }

        // Print the average time for this thread count
        printf("Average time using %d threads: %f seconds\n\n", thread_num, total_time / 10.0);
    }
    return 0;
}