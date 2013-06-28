#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <cmath>

#include "matrix.h"

int sMatrixMult(float* matrixA, int Am, int An, float* matrixB, int Bm, int Bn, float* restltMatrix );
int matrixEquil(float *matrixA, float *matrixB, int m, int n);
void speedup (int Am, int An, int Bm, int Bn, int numIter);
void alternateSize (int maxSize);
void alternateThreads(int maxThreads);

int main(int argc,char **argv)
{
    float* A = new float[100 * 100];
    float* B = new float[100 * 100];
    float* C = new float[100 * 100];
    float* D = new float[100 * 100];

    for (int i = 0; i < 100 * 100; i++)
    {
        A[i] = (float)rand() / RAND_MAX;
        B[i] = (float)rand() / RAND_MAX;
    }

    sMatrixMult (A, 100, 100, B, 100, 100, C);
    pMatrixMult (A, 100, 100, B, 100, 100, D);

    if (matrixEquil(C, D, 100, 100) == 0)
    {
        printf("YAY, your parallel results are verified\n");
        alternateSize(8);
        alternateThreads(16);
    }else
    {
        printf("OH NO, your parallel results are not verified\n");
    }

    delete[] A;
    delete[] B;
    delete[] C;
    delete[] D;
}

void alternateThreads (int maxThreads)
{
    double temp, pTime, sTime, sUp;
    float* A = new float[100 * 100];
    float* B = new float[100 * 100];
    float* C = new float[100 * 100];
    for (int i = 0; i < 100 * 100; i++)
    {
        A[i] = (float)rand() / RAND_MAX;
        B[i] = (float)rand() / RAND_MAX;
    }
    temp = omp_get_wtime();
    sMatrixMult (A, 100, 100, B, 100, 100, C);
    sTime = omp_get_wtime() - temp;

    for (int i = 0; i < maxThreads; i++)
    {
        for (int j = 0; j < 100 * 100; j++)
        {
            A[j] = (float)rand() / RAND_MAX;
            B[j] = (float)rand() / RAND_MAX;
        }

        omp_set_num_threads(i);
        temp = omp_get_wtime();
        pMatrixMult (A, 100, 100, B, 100, 100, C);
        pTime = omp_get_wtime() - temp;
        sUp = sTime / pTime;
        printf("\n%i threads took %f seconds. That's a speed up of %f\n", i, sTime, sUp);
    }
}

void alternateSize (int maxSize)
{
    int step = 500/maxSize, num = 0;
    for (int i = 0; i < maxSize; i++)
    {
        num = num + step;
        speedup (num, num, num, num, 5);
    }
}


void speedup (int Am, int An, int Bn, int Bm, int numIter)
{
    double sTime = 0.0, pTime = 0.0, sUp = 0.0, temp;
    float* A = new float[Am * An];
    float* B = new float[Bm * Bn]; 
    float* C = new float[Am * Bn];
    for (int i = 0; i < numIter; i++)
    {
        for (int i = 0; i < Am * An; i++)
            A[i] = (float)rand() / RAND_MAX;
        for (int i = 0; i < Bm * Bn; i++)
            B[i] = (float)rand() / RAND_MAX;

        temp = omp_get_wtime();
        sMatrixMult(A, Am, An, B, Bm, Bn, C);
        sTime = (omp_get_wtime() - temp);

        for (int i = 0; i < Am * An; i++)
            A[i] = (float)rand() / RAND_MAX;
        for (int i = 0; i < Bm * Bn; i++)
            B[i] = (float)rand() / RAND_MAX;

        temp = omp_get_wtime();
        pMatrixMult (A, Am, An, B, Bm, Bn, C);
        pTime = pTime + (omp_get_wtime() - temp);
    }

    sTime = sTime / numIter;
    pTime = pTime / numIter;
    sUp = sTime / pTime;

    printf("\n---====Problem size A = %i x %i; B = %i x %i ====---\n", Am, An, Bm, Bn);
    printf("The serial execution took %f seconds.\n", sTime);
    printf("The parallel execution took %f seconds.\n", pTime);
    printf("That's a speed up of %f.\n", sUp);

    delete [] A;
    delete [] B;
    delete [] C;
}

int sMatrixMult( float* matrixA, int Am, int An, float* matrixB, int Bm, int Bn, float* restltMatrix )
{
  if ( An != Bm )
    return 1;

  for ( int y = 0; y < Am; y++ )
  {
    for ( int x = 0; x < Bn; x++ )
    {
      restltMatrix[y*Bn + x] = 0.0f;
      for ( int z = 0; z < An; z++ )
        restltMatrix[y*Bn + x] = restltMatrix[y*Bn + x] + matrixA[y*An + z] * matrixB[z*Bn + x];
    }
  }
    return 0;
}


  int matrixEquil(  float *matrixA, float *matrixB, int m, int n )
{
  int bad = 0;
  for ( int y = 0; y < m && !bad ; y++ )
  {
    for ( int x = 0; x < n && !bad ; x++ )
    {
      if ( matrixA[y*n+x] != matrixB[y*n+x] )
      {
        bad++;
      }
    }
  }
  return bad;
}

