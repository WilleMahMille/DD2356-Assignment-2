#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

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

    for (size_t i = 0; i < size; i++)
    {
        sum_val += x[i];
    }

    return sum_val;
}

int main()
{

    // Create a n array of size 10^7 size of ints
    size_t size = 1e7;
    double *myList = (double *)malloc(size * sizeof(double));
    omp_get_wtime();

    generate_random(myList, size);

    printf("Sum: %f\n", serial_sum(myList, size));
}