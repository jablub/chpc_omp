#include <omp.h>  //include OMP library
#include <stdio.h>

void firstprivate() {

	int val = 2;

#pragma omp parallel firstprivate(val)
	{
		val = val * val;
		printf("val = %d (Thread %d)\n", val, omp_get_thread_num());
	}

	printf("val = %d \n", val);

}
