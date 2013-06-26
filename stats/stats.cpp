#include <omp.h>
#include <math.h>
#include <time.h>

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


// This is the parallel implementation.  You will have to parallelise it
// It calculates the minimum, maximum, sum, mean and standard deviation
stats pStats(double array[], unsigned int length)
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
  //TODO: Parallelise this loop
  for (unsigned int i = 0; i < length; i++ )
    sumSqurs += (  myStats.mean - array[i] ) * (  myStats.mean - array[i] ) ;

  // Now calculate the standard deviation
  myStats.stdDev = sqrt(sumSqurs/(double)length);

  return myStats;
}
