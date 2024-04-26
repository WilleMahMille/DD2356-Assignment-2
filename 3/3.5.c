#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

void generate_random(double *input, size_t size)
{

    for (size_t i = 0; i < size; i++)
    {
        input[i] = rand() / (double)(RAND_MAX);
    }
}

typedef struct
{
    double sum;
    int id;
    char pad[128];
} local_sum_t;

double omp_local_sum(double *x, size_t size)
{

    double start = omp_get_wtime();
    double sum = 0.0;
    double local_sum = 0.0;
#pragma omp parallel private(local_sum)
    {
        local_sum = 0.0;
#pragma omp for
        for (size_t i = 0; i < size; i++)
        {
            local_sum += x[i];
        }
        sum += local_sum;
    }
    return omp_get_wtime() - start;
}

int main()
{
    // Create a iterations array of size 10^7 size of ints
    size_t size = 1e7;
    double *myList = (double *)malloc(size * sizeof(double));

    const int iterations = 10;
    double *omp_local_time = (double *)malloc(iterations * sizeof(double));
    int thread_list[] = {1, 32, 64, 128};
    int nthreads = sizeof(thread_list) / sizeof(int);

    for (int j = 0; j < nthreads; j++)
    {
        omp_set_num_threads(thread_list[j]);
        printf("Number of threads: %d\n", thread_list[j]);
        for (int i = 0; i < iterations; i++)
        {
            generate_random(myList, size);
            omp_set_num_threads(thread_list[j]);
            omp_local_time[i] = omp_local_sum(myList, size);
        }
        double avg_time = 0.0;
        for (int i = 0; i < iterations; i++)
        {
            avg_time += omp_local_time[i];
        }
        avg_time /= iterations;
        double std_time = 0.0;
        for (int i = 0; i < iterations; i++)
        {
            std_time += (omp_local_time[i] - avg_time) * (omp_local_time[i] - avg_time);
        }
        std_time = sqrt(std_time / iterations);

        printf("Average time: %f\n", avg_time);
        printf("Standard deviation: %f\n", std_time);
        printf("-------------------\n");
    }

    return 0;
}