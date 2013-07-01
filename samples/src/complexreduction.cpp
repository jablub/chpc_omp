#include <omp.h>  //include OMP library
#include <stdio.h>
#include "demos.h"


void complexreduction() {

	int num = 10;
	int vals[num];
	init(vals, num);
	int numops = 0;
	int sum = 0;
	int product = 1;

#pragma omp parallel for reduction(+ : sum, numops) reduction (* : product)
	for (int i = 0; i < num; i++) {
		sum += vals[i];
		product *= vals[i];
		numops++;
	}

	printf("sum = %d \n", sum);
	printf("product = %d \n", product);
	printf("numops = %d \n", numops);
}

