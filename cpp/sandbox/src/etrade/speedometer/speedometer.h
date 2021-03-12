#if !defined ETRADE__SPEEDOMETER_H
#define ETRADE__SPEEDOMETER_H

#include "etrade/types.cpp"  // ETrade::t
#include "lib/formatted.cpp" // Formatted
#include <string>            // std::string
#include <utility>           // std::pair
#include <vector>            // std::vector

using quote_t = ETrade::t::quote_t;

namespace ETrade {
class Speedometer {
public:
  Speedometer(std::vector<quote_t> *quotes_ptr_) : quotes_ptr(quotes_ptr_){};

  std::pair<int, double> average_displacement(const int);
  std::pair<int, double> average_velocity(const int);
  std::pair<int, double> simple_moving_average(const int);

  std::string seconds_to_time(const int);

  void log();

private:
  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::vector<quote_t> *quotes_ptr;

  void log_average_velocity(const int);
  void log_displacement();
  void log_simple_moving_average();
};
} // namespace ETrade

#endif
