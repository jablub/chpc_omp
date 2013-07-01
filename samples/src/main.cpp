#include <omp.h>  //include OMP library
#include <stdio.h>

#include "demos.h"

int main(int argc, char *argv[]) {

	printf("\n  \n");

	printf("\n hello \n");
	hello();

	printf("\n forkjoin \n");
	forkjoin();

	printf("\n single \n");
	single();

	printf("\n forloop \n");
	forloop();

	printf("\n badloop \n");
	badloop();


	printf("\n goodloop \n");
	goodloop();

	printf("\n pirate \n");
	pirate();

	printf("\n firstprivate \n");
	firstprivate();


	printf("\n lastprivate \n");
	lastprivate();

	printf("\n simplereduction \n");
	simplereduction();

	printf("\n complexreduction \n");
	complexreduction();

	printf("\n barrier \n");
	barrier();

	printf("\n master \n");
	master();

	printf("\n critical \n");
	critical();

	printf("\n namedcritical \n");
	namedcritical();

	printf("\n atomiccowboy \n");
	atomiccowboy();

}

void init(int* v, int num) {
	for (int i = 0; i < num; i++) {
		v[i] = i + 1;
	}
}

