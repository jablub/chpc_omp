#include <omp.h>  //include OMP library
#include <stdio.h>

void forkjoin() {

	printf("\nHello? \n\n");

	// FORK
#pragma omp parallel
	{
		printf("Hello from thread = %d\n", omp_get_thread_num());
	}	// JOIN

	printf("\nHi guys! \n\n");

	// FORK
#pragma omp parallel
	{
		printf("Hello from thread = %d\n", omp_get_thread_num());
	}	// JOIN

	printf("\nOoookayyy... \n");
}

