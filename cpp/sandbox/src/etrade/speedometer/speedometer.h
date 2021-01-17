#if !defined ETRADE__SPEEDOMETER_H
#define ETRADE__SPEEDOMETER_H

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include <vector>            // std::vector

namespace ETrade {
class Speedometer {
public:
  std::vector<double> accelerations;
  double momentum = 0.00;
  std::vector<double> velocities;

  void log();
  void tick(const json &);

  Speedometer(int interval) : polling_interval(interval){};

private:
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  int polling_interval;

  double compute_average(const std::vector<double> &, const int);
};
} // namespace ETrade

#endif
