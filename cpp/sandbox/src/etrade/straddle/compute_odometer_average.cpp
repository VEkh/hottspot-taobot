#if !defined ETRADE__STRADDLE_compute_odometer_average
#define ETRADE__STRADDLE_compute_odometer_average

#include "straddle.h" // ETrade::Straddle, POLLING_INTERVAL_SECONDS
#include <numeric>    // std::accumulate
#include <vector>     // std::vector

double ETrade::Straddle::compute_odometer_average(
    const std::vector<double> &collection, const int period) {
  const int ticks = period / POLLING_INTERVAL_SECONDS;

  if (collection.size() < ticks) {
    return 0;
  }

  return std::accumulate(collection.end() - ticks, collection.end(), 0.0) /
         ticks;
}

#endif
