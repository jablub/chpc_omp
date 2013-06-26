#include "stats.h"
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <cmath>

using namespace std;

bool test (stats a, stats b);
double speedup(unsigned int length, int numIter);
void alternateSize (int maxSize);
void alternateThreads(int maxThreads);

int main(int argc,char **argv)
{
    unsigned int length = 1000;

    double data[length];

    for (int i = 0; i < length; i++)
        data[i] = (double)rand() / RAND_MAX;

    stats sStat = sStats (data, length);
    stats pStat = pStats (data, length);

    if(test(sStat, pStat))
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
    unsigned int length = 1000;
    double data[length];

    for (int i = 0; i < length; i++)
        data[i] = (double)rand() / RAND_MAX;

    temp = omp_get_wtime();
    sStats (data, length);
    sTime = omp_get_wtime() - temp;

    for (int i = 0; i < maxThreads; i++)
    {
        for (int j = 0; j < length; j++)
            data[j] = (double)rand() / RAND_MAX;
        omp_set_num_threads(i);
        temp = omp_get_wtime();
        pStats (data, length);
        pTime = omp_get_wtime() - temp;
        sUp = sTime / pTime;
        printf("\n%i threads took %f seconds. That's a speed up of %f\n", i, sTime, sUp);
    }
}

void alternateSize (int maxSize)
{
    int step = 1000000/maxSize, num = 0;
    for (int i = 0; i < maxSize; i++)
    {
        num = num + step;
        speedup (num, 5);
    }
}

bool test (stats a, stats b)
{
    bool ret = true;
    if (a.min != b.min)
    {
        ret = false;
        printf ("Serial min = %f != %f = parallel min\n", a.min, b.min);
    }
    if (a.max != b.max)
    {
        ret = false;
        printf ("Serial max = %f != %f = parallel max\n", a.min, b.min);
    }
    if (abs(a.sum - b.sum) > 10e-12)
    {
        ret = false;
        printf ("Serial sum = %f != %f = parallel sum\n", a.sum, b.sum);
    }
    if (abs(a.mean - b.mean) > 10e-12)
    {
        ret = false;
        printf ("Serial mean = %f != %f = parallel mean\n", a.mean, b.mean);
    }
    if (abs(a.stdDev - b.stdDev) > 10e-12)
    {
        ret = false;
        printf ("Serial stdDev = %f != %f = parallel stdDev\n", a.stdDev, b.stdDev);
    }
    return ret;
}

double speedup (unsigned int length, int numIter)
{
    double sTime = 0.0, pTime = 0.0, sUp = 0.0, temp; 
    stats tempStat;
    double data[length];

    for (int i = 0; i < numIter; i++)
    {
        for (int i = 0; i < length; i++)
            data[i] = (double)rand() / RAND_MAX;

        temp = omp_get_wtime();
        tempStat = sStats(data, length);
        sTime = (omp_get_wtime() - temp);

        for (int i = 0; i < length; i++)
            data[i] = (double)rand() / RAND_MAX;

        temp = omp_get_wtime();
        tempStat = pStats (data, length);
        pTime = pTime + (omp_get_wtime() - temp);
    }

    sTime = sTime / numIter;
    pTime = pTime / numIter;
    sUp = sTime / pTime;

    printf("\n---====Problem size %i====---\n",  length);
    printf("The serial execution took %f seconds.\n", sTime);
    printf("The parallel execution took %f seconds.\n", pTime);
    printf("That's a speed up of %f.\n", sUp);

}
