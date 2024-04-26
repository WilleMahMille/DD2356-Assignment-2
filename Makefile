compile-1:
	gcc 1/1.c -o 1/1.out -fopenmp
run-1: 
	./1/1.out
compile-3:
	gcc 3/sum.c -o 3/sum.out -fopenmp
run-3: 
	./3/sum.out