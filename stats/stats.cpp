#include <omp.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>


#include "stats.h"

using namespace std;


// This is the serial implementation DO NOT edit it
// It calculates the minimum, maximum, sum, mean and standard deviation
stats sStats(double array[], unsigned int length)
{
  // A struct to hold the relevant stats
  stats myStats;
  myStats.min = array[0];
  myStats.max = array[0];
  myStats.sum = 0;
  myStats.mean = 0;
  myStats.stdDev = 0;

  // First iteration, find min, max and sum
  for (unsigned int i = 0; i < length; i++ )
  {
    myStats.sum += array[i];

    if ( array[i] < myStats.min )
      myStats.min = array[i];

    if ( array[i] > myStats.max )
      myStats.max = array[i];
  }

  // use sum to calc mean
  myStats.mean = myStats.sum / (double)length;

  //second pass to calculate sum of squared differences from the mean
  double sumSqurs = 0;
  for (unsigned int i = 0; i < length; i++ )
    sumSqurs += (  myStats.mean - array[i] ) * (  myStats.mean - array[i] ) ;

  // Now calculate the standard deviation
  myStats.stdDev = sqrt(sumSqurs/(double)length);

  return myStats;
}

stats pStats_not(double array[], unsigned int length)
{
  // A struct to hold the relevant stats
  stats myStats;
  myStats.min = array[0];
  myStats.max = array[0];
  myStats.sum = 0;
  myStats.mean = 0;
  myStats.stdDev = 0;

  // First iteration, find min, max and sum
  for (unsigned int i = 0; i < length; i++ )
  {
    myStats.sum += array[i];

    if ( array[i] < myStats.min )
      myStats.min = array[i];

    if ( array[i] > myStats.max )
      myStats.max = array[i];
  }

  // use sum to calc mean
  myStats.mean = myStats.sum / (double)length;

  //second pass to calculate sum of squared differences from the mean
  double sumSqurs = 0;
  for (unsigned int i = 0; i < length; i++ )
    sumSqurs += (  myStats.mean - array[i] ) * (  myStats.mean - array[i] ) ;

  // Now calculate the standard deviation
  myStats.stdDev = sqrt(sumSqurs/(double)length);

  return myStats;
}


stats pStats_reduct(double array[], unsigned int length)
{
  // A struct to hold the relevant stats
  stats myStats;
  myStats.min = array[0];
  myStats.max = array[0];
  myStats.sum = 0;
  myStats.mean = 0;
  myStats.stdDev = 0;

  // First iteration, find min, max and sum
  //TODO: Parallelise this step
  double mini = DBL_MAX, maxi = -DBL_MAX, sum = 0;
//#pragma omp parallel for reduction (+ : sum) reduction (max : maxi) reduction (min : mini)
  for (unsigned int i = 0; i < length; i++ )
  {
    sum += array[i];

    if ( array[i] < mini ) {
      mini = array[i];
    }

    if ( array[i] > maxi ) {
      maxi = array[i];
    }

  }
  myStats.sum = sum;
  myStats.min = mini;
  myStats.max = maxi;

  // use sum to calc mean
  myStats.mean = myStats.sum / (double)length;

  //second pass to calculate sum of squared differences from the mean
  double sumSqurs = 0;
  //TODO: Parallelise this loop
//#pragma omp parallel for reduction (+ : sumSqurs)
  for (unsigned int i = 0; i < length; i++ ) {
    sumSqurs += (  myStats.mean - array[i] ) * (  myStats.mean - array[i] ) ;
  }

  // Now calculate the standard deviation
  myStats.stdDev = sqrt(sumSqurs/(double)length);

  return myStats;
}


stats pStats_atom(double array[], unsigned int length)
{
  // A struct to hold the relevant stats
  stats myStats;
  myStats.min = array[0];
  myStats.max = array[0];
  myStats.sum = 0;
  myStats.mean = 0;
  myStats.stdDev = 0;

  // First iteration, find min, max and sum
  //TODO: Parallelise this step
  double mini = DBL_MAX, maxi = -DBL_MAX;
#pragma omp parallel for
  for (unsigned int i = 0; i < length; i++ )
  {
#pragma omp atomic update
	myStats.sum += array[i];
  }

#pragma omp parallel for reduction (max : maxi) reduction (min : mini)
  for (unsigned int i = 0; i < length; i++ )
  {
    if ( array[i] < mini ) {
    	mini = array[i];
    }

    if ( array[i] > maxi ) {
    	maxi = array[i];
    }

  }
  myStats.min = mini;
  myStats.max = maxi;

  // use sum to calc mean
  myStats.mean = myStats.sum / (double)length;

  //second pass to calculate sum of squared differences from the mean
  double sumSqurs = 0;
  //TODO: Parallelise this loop
#pragma omp parallel for reduction (+ : sumSqurs)
  for (unsigned int i = 0; i < length; i++ ) {
    sumSqurs += (  myStats.mean - array[i] ) * (  myStats.mean - array[i] ) ;
  }

  // Now calculate the standard deviation
  myStats.stdDev = sqrt(sumSqurs/(double)length);

  return myStats;
}



// This is the parallel implementation.  You will have to parallelise it
// It calculates the minimum, maximum, sum, mean and standard deviation
stats pStats(double array[], unsigned int length){
//	return pStats_atom(array, length);
//	return pStats_reduct(array, length);
	return pStats_not(array, length);
}

