#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){

    // global variables
    int VALEUR1 = 1000;
    int VALEUR2 = 2000;

    // private variables
    #pragma omp parallel private(VALEUR2)
    {
        // printf("Hello from process: %d\n", omp_get_thread_num());
        // increment VALUR2 by 1 in each thread
        VALEUR2++;
        printf("Thread %d: VALEUR1 = %d, VALEUR2 = %d\n", omp_get_thread_num(), VALEUR1, VALEUR2);
    }
    return 0;
}