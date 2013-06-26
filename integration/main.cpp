#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <cmath>

#include "integration.h"

using namespace std;

double sTrapezoid(double a, double b, unsigned int numsteps);
bool test (double a, double b);
double speedup (double a, double b, unsigned int numsteps, int numIter);
void alternateSize (int maxSize);
void alternateThreads(int maxThreads);

int main(int argc,char **argv)
{
    unsigned int numSteps = 10000;

    double serial = sTrapezoid(1.0, 5.0, numSteps);
    double parallel = pTrapezoid(1.0, 5.0, numSteps);

    printf ("Serial = %f\n", serial);
    printf ("Parallel = %f\n", parallel);

    if (test(serial, parallel))
    {
        printf("YAY, your parallel results are verified\n");
        alternateSize(8);
        alternateThreads(16);
    }else
    {
        printf("OH NO, your parallel results are not verified\n");
    }
}

void alternateThreads (int maxThreads)
{
    double temp, pTime, sTime, sUp;
    temp = omp_get_wtime();
    sTrapezoid (1.0, 5.0, 100000);
    sTime = omp_get_wtime() - temp;

    for (int i = 0; i < maxThreads; i++)
    {
        omp_set_num_threads(i);
        temp = omp_get_wtime();
        pTrapezoid (1.0, 5.0, 100000);
        pTime = omp_get_wtime() - temp;
        sUp = sTime / pTime;
        printf("\n%i threads took %f seconds. That's a speed up of %f\n", i, sTime, sUp);
    }
}

void alternateSize (int maxSize)
{
    int step = 10000000/maxSize, num = 0;
    for (int i = 0; i < maxSize; i++)
    {
        num = num + step;
        speedup (0.0, 100.0, num, 5);
    }
}

double speedup (double a, double b, unsigned int numsteps, int numIter)
{
    double sTime = 0.0, pTime = 0.0, sUp = 0.0, temp, tempVal; 
    for (int i = 0; i < numIter; i++)
    {
        temp = omp_get_wtime();
        tempVal = sTrapezoid(a, b, numsteps);
        sTime = (omp_get_wtime() - temp);

        temp = omp_get_wtime();
        tempVal = pTrapezoid (a, b, numsteps);
        pTime = pTime + (omp_get_wtime() - temp);
    }

    sTime = sTime / numIter;
    pTime = pTime / numIter;
    sUp = sTime / pTime;

    printf("---====Problem size %i====---\n",  numIter);
    printf("The serial execution took %f seconds.\n", sTime);
    printf("The parallel execution took %f seconds.\n", pTime);
    printf("That's a speed up of %f.\n", sUp);
    return sUp;
}

bool test (double a, double b)
{
    double error = abs(a - b);
    if (error > 10e-12)
        return false;
    return true;
}

double sTrapezoid(double a, double b, unsigned int numsteps)
{
  double r = 0.0;
  double x = a;
  double h = (b - a) / (double)numsteps;

  for (unsigned int i = 1; i < numsteps; i++)
  {
    x += h;
    r += f(x);
  }

  r = (r + (f(a) + f(b)) / 2.0) * (b - a) / (double)numsteps;
  return r;
}