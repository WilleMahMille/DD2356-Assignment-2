#include <stdio.h>
#include <omp.h>

int main()
{
    int nthreads = 4;
    int thread_id;

#pragma omp parallel private(thread_id)
    {
        thread_id = omp_get_thread_num();
        printf("Hello World from thread %d!\n", thread_id);
    }
}