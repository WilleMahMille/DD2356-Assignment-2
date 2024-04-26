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

double serial_sum(double *x, size_t size)
{
    double sum_val = 0.0;
    double start = omp_get_wtime();

    for (size_t i = 0; i < size; i++)
    {
        sum_val += x[i];
    }

    return omp_get_wtime() - start;
}

double omp_sum(double *x, size_t size)
{
    double sum_val = 0.0;
    double start = omp_get_wtime();

#pragma omp parallel for reduction(+ : sum_val)
    for (size_t i = 0; i < size; i++)
    {
        sum_val += x[i];
    }

    return omp_get_wtime() - start;
}

double omp_critical_sum(double *x, size_t size)
{
    double sum_val = 0.0;

    double start = omp_get_wtime();

#pragma omp parallel for
    for (size_t i = 0; i < size; i++)
    {
#pragma omp critical
        sum_val += x[i];
    }

    return omp_get_wtime() - start;
}

int main()
{

    // Create a iterations array of size 10^7 size of ints
    size_t size = 1e7;
    double *myList = (double *)malloc(size * sizeof(double));

    const int iterations = 10;
    double *serial_time = (double *)malloc(iterations * sizeof(double));
    double *omp_time = (double *)malloc(iterations * sizeof(double));
    double *omp_critical_time = (double *)malloc(iterations * sizeof(double));
    int thread_list[] = {1, 2, 4, 8, 16, 20, 24, 28, 32};
    int nthreads = sizeof(thread_list);

    for (int i = 0; i < iterations; i++)
    {
        generate_random(myList, size);
        serial_time[i] = serial_sum(myList, size);
    }
    double serial_avg = 0;
    for (int i = 0; i < iterations; i++)
    {
        serial_avg += serial_time[i];
    }
    serial_avg /= iterations;
    double serial_std = 0;
    for (int i = 0; i < iterations; i++)
    {
        serial_std += (serial_time[i] - serial_avg) * (serial_time[i] - serial_avg);
    }
    serial_std = sqrt(serial_std / iterations);
    printf("Serial time average: %f\n", serial_avg);
    printf("Serial std: %f\n", serial_std);

    // Parallel
    for (int j = 0; j < nthreads; j++)
    {
        omp_set_num_threads(thread_list[j]);
        printf("Number of threads: %d\n", thread_list[j]);

        for (int i = 0; i < iterations; i++)
        {
            generate_random(myList, size);
            serial_time[i] = serial_sum(myList, size);
            omp_time[i] = omp_sum(myList, size);
            omp_critical_time[i] = omp_critical_sum(myList, size);
        }
        double omp_avg = 0;
        double omp_critical_avg = 0;
        for (int i = 0; i < iterations; i++)
        {
            omp_avg += omp_time[i];
            omp_critical_avg += omp_critical_time[i];
        }
        omp_avg /= iterations;
        omp_critical_avg /= iterations;
        double omp_std = 0;
        double omp_critical_std = 0;
        for (int i = 0; i < iterations; i++)
        {
            omp_std += (omp_time[i] - omp_avg) * (omp_time[i] - omp_avg);
            omp_critical_std += (omp_critical_time[i] - omp_critical_avg) * (omp_critical_time[i] - omp_critical_avg);
        }
        omp_std = sqrt(omp_std / iterations);
        omp_critical_std = sqrt(omp_critical_std / iterations);
        printf("OMP time average: %f\n", omp_avg);
        printf("OMP std: %f\n", omp_std);
        printf("OMP critical time average: %f\n", omp_critical_avg);
        printf("OMP critical std: %f\n", omp_critical_std);
    }
}