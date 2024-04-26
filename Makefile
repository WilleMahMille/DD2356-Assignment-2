compile-1:
	gcc 1/1.c -o 1/1.out -fopenmp
run-1: 
	./1/1.out
compile-3:
	gcc 3/sum.c -o 3/sum.out -fopenmp -lm
run-3:
	./3/sum.out
3: compile-3 run-3
compile-3-4:
	gcc 3/3.4.c -o 3/3.4.out -fopenmp -lm
run-3-4:
	./3/3.4.out
3-4: compile-3-4 run-3-4
compile-3-5:
	gcc 3/3.5.c -o 3/3.5.out -fopenmp -lm
run-3-5:
	./3/3.5.out
3-5: compile-3-5 run-3-5

compile-4:
	gcc 4/dftw.c -o 4/dftw.out -fopenmp -lm
run-4:
	./4/dftw.out
4: compile-4 run-4