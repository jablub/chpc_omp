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
double pTrapezoid(double a, double b, unsigned int imax)
{
  //f(a) will return, well f(a)  function pointers for the win!
  // TODO: You must implment this section, first so it validates
  // Then optamise it to run in parellel

  return f(a); // This will return f(a) for the function you specifyed in setFunction.  This is just an example, this will NOT validate
}
