#include <omp.h>  //include OMP library
#include <stdio.h>
#include <unistd.h>

#define N 20

void critical() {

	int inc = 0;
#pragma omp parallel for
	for (int i = 0; i < N; ++i) {

		printf("Iteration %d  (Thread %d)\n", i, omp_get_thread_num());
		usleep(10);
#pragma omp critical
		{
			inc++;
			if (inc == N) {
				printf("Last Thread  (Thread %d)\n", omp_get_thread_num());
			}
		}
	}
}

