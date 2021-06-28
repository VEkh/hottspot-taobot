#ifndef UTILS__INTEGER
#define UTILS__INTEGER

#include <iomanip>  // std::setw
#include <iostream> // std::fixed
#include <math.h>   // pow, round
#include <sstream>  // std::stringstream
#include <string>   // std::string

namespace utils {
namespace integer_ {
std::string seconds_to_clock(const int seconds) {
  std::ostringstream out;

  const int hours = seconds / (60 * 60);
  const int minutes = (seconds % (60 * 60)) / 60;
  const int remainder_seconds = seconds % 60;

  if (hours) {
    out << std::setfill('0') << std::setw(2) << hours << ":";
  }

  out << std::setfill('0') << std::setw(2) << minutes << ":"
      << std::setfill('0') << std::setw(2) << remainder_seconds;

  return out.str();
}
} // namespace integer_
} // namespace utils
#endif
