#include <omp.h>  //include OMP library
#include <stdio.h>

void hello() {

#pragma omp parallel
	{
		printf("Hello World from thread = %d\n", omp_get_thread_num());
	}
}

