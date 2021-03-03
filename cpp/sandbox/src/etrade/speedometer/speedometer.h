#if !defined ETRADE__SPEEDOMETER_H
#define ETRADE__SPEEDOMETER_H

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include <utility>           // std::pair

namespace ETrade {
class Speedometer {
public:
  Speedometer(json *quotes_ptr_) : quotes_ptr(quotes_ptr_){};

  std::pair<int, double> average_displacement(const int);
  std::pair<int, double> average_velocity(const int);
  void log();

private:
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  json *quotes_ptr;

  void log_displacement();
  void log_average_velocity(const int);
};
} // namespace ETrade

#endif
