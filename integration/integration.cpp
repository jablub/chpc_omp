#include <omp.h>
#include <math.h>
#include <stdlib.h>

#include "integration.h"

using namespace std;

double f(double x)
{
  return x;
}

// This is a parallel implementation of the Trapezoidal rule.
double pTrapezoid(double a, double b, unsigned int imax)
{
  //f(a) will return, well f(a)  function pointers for the win!
  // TODO: You must implement this section, first so it validates
  // Then optimise it to run in parallel

  return f(a); // This is just an example, this will NOT validate.
}
