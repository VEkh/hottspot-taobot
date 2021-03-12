#if !defined UTILS__FLOAT
#define UTILS__FLOAT

#include <iomanip>  // std::setw
#include <iostream> // std::fixed
#include <math.h>   // pow, round
#include <sstream>  // std::stringstream
#include <string>   // std::string

namespace utils {
namespace float_ {
double round_to(double input, int precision) {
  int normalizer = pow(10, precision);
  return round(input * normalizer) / normalizer;
}

double to_currency(float val) { return round_to(val, 2); }

std::string to_rounded_percentage(float val) {
  std::stringstream result;

  result << std::setprecision(4) << std::fixed << (val * 100.0);
  return result.str();
}
} // namespace float_
} // namespace utils
#endif
