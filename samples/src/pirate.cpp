#include <omp.h>  //include OMP library
#include <stdio.h>

void pirate() {

	int i = 0;

//	This should cause a race condition
#pragma omp parallel
	{
		i++;
		printf("i=%d  (Thread %d)\n", i, omp_get_thread_num());

	}

	printf("\n Try again \n");

#pragma omp parallel private (i)
	{
		i++;
		printf("i=%d  (Thread %d)\n", i, omp_get_thread_num());
	}
}

