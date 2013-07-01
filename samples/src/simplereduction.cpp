#include <omp.h>  //include OMP library
#include <stdio.h>
#include "demos.h"


void simplereduction() {

	int num = 10;
	int vals[num];
	init(vals, num);
	int sum = 0;


	// Sequential
	for (int i = 0; i < num; i++) {
		sum += vals[i];
		printf("%d + ", vals[i]);
	}

	printf("0 = %d \n", sum);
	sum = 0;  // reset

	// Parallel
#pragma omp parallel for reduction(+ : sum)
	for (int i = 0; i < num; i++) {
		sum += vals[i];
		printf("%d + ", vals[i]);
	}

	printf("0 = %d \n", sum);


}

