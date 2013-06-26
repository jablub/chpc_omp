#include <omp.h>
#include <math.h>
#include <stdlib.h>

#include "integration.h"

using namespace std;

double f(double x)
{
  return x;
}

// This is a parelle implimentaion of the Trapezoidal rule.
double pTrapezoid(double a, double b, unsigned int numsteps)
{
  //f(a) will return, well f(a)  function pointers for the win!
  // TODO: You must implment this section, first so it validates
  // Then optamise it to run in parellel

	double r = 0.0;
	double x = a;
	double h = (b - a) / (double)numsteps;
#pragma omp barrier

#pragma omp parallel for private (x) reduction (+ : r)
	for (unsigned int i = 1; i < numsteps; i++)
	{
		x += h;
		r += f(x);
	}

	r = (r + (f(a) + f(b)) / 2.0) * (b - a) / (double)numsteps;
	return r;

}
