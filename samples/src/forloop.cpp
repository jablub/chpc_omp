#include <omp.h>  //include OMP library
#include <stdio.h>

void forloop() {

//#pragma omp parallel
//	{
//#pragma omp for
//		for (int i = 0; i < 12; i++) {
//			printf("Hello Looper from thread = %d\n", omp_get_thread_num());
//		}
//	}

#pragma omp parallel for
	for (int i = 0; i < 12; i++) {
		printf("Hello Looper from thread = %d   (i=%d  at  %p) \n", omp_get_thread_num(), i, &i);
	}

}

