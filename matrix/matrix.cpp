#include <omp.h>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "matrix.h"


using namespace std;

// This is the parallel implementaion of a simple matrix multiplication
// NOTE: matices are row major with 0 0 in the top left

// matrixA:   Pointer to the first element in a Am x An array
// Am     Number of rows in matrixA
// Am     Number of colums in matrixA
// Same for stuff for B
// restltMatrix:  Where you need to write the results to
int pMatrixMult( float* matrixA, int Am, int An, float* matrixB, int Bm, int Bn, float* restltMatrix )
{
  // Check if we can multiply
  if ( An != Bm )
    return 1;

  // eg on how to access the ( y x ) item in matrixA.  This is just an example of how to acces the data.
  //float ym =  matrixA[y*Am + x];  // read value
  //matrixA[y*Am + x] = ym;         // assign value

  //TODO: Implement matrix multiplication and parallelise it
 
  #pragma omp parallel 
  {  
	  #pragma omp for
	  for ( int y = 0; y < Am; y++ )
	  {
		for ( int x = 0; x < Bn; x++ )
		{
		  restltMatrix[y*Bn + x] = 0.0f;
		  for ( int z = 0; z < An; z++ )
			restltMatrix[y*Bn + x] = restltMatrix[y*Bn + x] + matrixA[y*An + z] * matrixB[z*Bn + x];
		}
	  }
  }

  return 0;
}

