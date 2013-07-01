#include <omp.h>  //include OMP library
#include <stdio.h>

void master() {

#pragma omp parallel
	{
		printf("Running  (Thread %d)\n", omp_get_thread_num());
#pragma omp master
		{
			printf("Master only (Thread %d)\n", omp_get_thread_num());
		}
	}
}

