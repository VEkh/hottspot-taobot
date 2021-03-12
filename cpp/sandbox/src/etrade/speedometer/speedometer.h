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

  void log();

private:
  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::vector<quote_t> *quotes_ptr;
};
} // namespace ETrade

#endif
