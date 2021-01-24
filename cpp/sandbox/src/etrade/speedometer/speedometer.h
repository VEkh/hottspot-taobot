#if !defined ETRADE__SPEEDOMETER_H
#define ETRADE__SPEEDOMETER_H

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted

namespace ETrade {
class Speedometer {
public:
  void log();

  Speedometer(json *quotes_ptr_) : quotes_ptr(quotes_ptr_){};

private:
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  json *quotes_ptr;

  void log_average(const int);
};
} // namespace ETrade

#endif
