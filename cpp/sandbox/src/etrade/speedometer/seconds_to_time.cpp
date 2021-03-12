#if !defined ETRADE__SPEEDOMETER_seconds_to_time
#define ETRADE__SPEEDOMETER_seconds_to_time

#include "speedometer.h" // ETrade::Speedometer
#include <iomanip>       // std::setfill, std::setw
#include <sstream>       // std::ostringstream
#include <string>        // std::string

std::string ETrade::Speedometer::seconds_to_time(const int in_seconds) {
  std::ostringstream out;

  const int minutes = in_seconds / 60;
  const int seconds = in_seconds % 60;

  out << std::setfill('0') << std::setw(2) << minutes << ":"
      << std::setfill('0') << std::setw(2) << seconds;

  return out.str();
}

#endif
