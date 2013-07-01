#include <omp.h>  //include OMP library
#include <stdio.h>
#include <unistd.h>

#define N 5

void atomiccowboy() {

	int inc = 1;
#pragma omp parallel for
	for (int i = 0; i < N; ++i) {

		printf("Iteration %d  (Thread %d)\n", i, omp_get_thread_num());
		usleep(10);
#pragma omp atomic
		inc = inc * inc++;
	}

	printf("inc %d\n", inc);

}

