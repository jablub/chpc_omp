#include <omp.h>  //include OMP library
#include <stdio.h>

void barrier() {

#pragma omp parallel
	{
		printf("Running  (Thread %d)\n", omp_get_thread_num());

#pragma omp barrier

		printf("Waiting  (Thread %d)\n", omp_get_thread_num());

#pragma omp barrier

		printf("Running  (Thread %d)\n", omp_get_thread_num());
	}
}

