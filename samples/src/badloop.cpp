#include <omp.h>  //include OMP library
#include <stdio.h>

void badloop() {

	int a[4] = { 1, 2, 3, 4 };

#pragma omp parallel for
	for (int i = 0; i < 4; i++) {
		if (i > 0) {
			a[i] = a[i] + a[i - 1];
		}
	}

	printf("[%d %d %d %d]\n", a[0], a[1], a[2], a[3]);


}

