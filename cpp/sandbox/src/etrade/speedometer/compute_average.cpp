#if !defined ETRADE__SPEEDOMETER_compute_average
#define ETRADE__SPEEDOMETER_compute_average

#include "speedometer.h" // ETrade::Speedometer, polling_interval
#include <numeric>       // std::accumulate
#include <vector>        // std::vector

double
ETrade::Speedometer::compute_average(const std::vector<double> &collection,
                                     const int period) {
  const int ticks = period / polling_interval;

  if (collection.size() < ticks) {
    return 0;
  }

  return std::accumulate(collection.end() - ticks, collection.end(), 0.0) /
         ticks;
}

#endif
