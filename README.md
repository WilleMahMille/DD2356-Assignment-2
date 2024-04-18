# Assignment 2

## Exercise 1 - Running in parallel

Compiile:

```bash
make compile-1
```

Run:

```bash
make run-1
```

### Questions

1. Write an OpenMP C code with each thread printing Hello World from Thread X! where X is the thread ID.s
2. How do you compile the code in question 1? Which compiler and flags have you used?
   We use the command `cc 1.c -o 1.out -fopenmp`, where the new flag is `-fopenmp`
3. How do you run the OpenMP code on Dardel? What flags did you set?
   We first compile the program as described in 2, then we requested an allocation, setting the flag `--cpus-per-task` to be the number of threads we wish to use.
   After that, we set the enviroment variable `OMP_NUM_THREADS` to the number of threads we wish to use as a default, and ran the program normally.
4. How many different ways can the number of threads in OpenMP be changed? Which are they?
   There are a couple of ways to change the number of threads in Dardel: `Environmental variables` where we define the amount of threads that should be available for the program. You can also use the runtime function `omp_set_num_threads` to set the number of threads to be available within the program. The last relevant way to setting the number of threads is through a clause in the program function that can be defined as follows: `#pragma omp parallel num_threads(4)`

## Exercise 2 - STREAM benchmark and the importance of threads

### Questions

1. Run the STREAM benchmark five times and record the average bandwidth values and its standard deviation for the copy kernel. Prepare a plot (with error bars) comparing the bandwidth using 1,32,64, and 128 threads.
2. How does the measured bandwidth with the copy kernel depend on the number of threads?
3. Prepare another plot comparing the bandwidth measured with copy kernel with static, dynamic, and guided schedules using 128 threads.
4. How do you set the schedule in the STREAM code? What is the fastest schedule, and why do you think it is so?
