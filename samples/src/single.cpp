#include <omp.h>  //include OMP library
#include <stdio.h>

void single() {

	// FORK
#pragma omp parallel
	{
		printf("Going (thread = %d)\n", omp_get_thread_num());

#pragma omp single
		printf("Only one thread running (thread = %d)\n",
				omp_get_thread_num());

		printf("Going again (thread = %d)\n", omp_get_thread_num());
	}	// JOIN

}

