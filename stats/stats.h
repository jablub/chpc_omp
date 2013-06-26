#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

struct stats
{
  double min;
  double max;
  double sum;
  double mean;
  double stdDev;
}; // min max sum mean stdDev

stats sStats(double array[], unsigned int length);
stats pStats(double array[], unsigned int length);

#endif // STATS_H_INCLUDED
