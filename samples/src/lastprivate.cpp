#include <omp.h>  //include OMP library
#include <stdio.h>

void lastprivate() {

	int val;

#pragma omp parallel for lastprivate(val)
	for (int i = 0; i < 12; i++) {
		val = i;
	}

	printf("val = %d \n", val);
}
