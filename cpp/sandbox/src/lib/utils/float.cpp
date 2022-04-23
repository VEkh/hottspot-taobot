#ifndef UTILS__FLOAT
#define UTILS__FLOAT

#include <iomanip>  // std::setprecision
#include <iostream> // std::fixed
#include <math.h>   // pow, round
#include <sstream>  // std::stringstream
#include <string>   // std::stod, std::string

namespace utils {
namespace float_ {
std::string round_to_s(double input, int precision) {
  std::stringstream out;

  out << std::setprecision(precision) << std::fixed << input;

  return out.str();
}

double round_to(double input, int precision) {
  return std::stod(round_to_s(input, precision));
}

double sigmoid(const double max, const double min, const double x,
               const double x_coefficient = 1.0, const double x_shift = 0.0) {
  const double y_shift = min;
  const double y_coefficient = max - min;
  return (y_coefficient / (1 + exp(-x_coefficient * (x - x_shift)))) + y_shift;
}

double to_currency(float val) { return round_to(val, 2); }

std::string to_rounded_percentage(double val) {
  std::stringstream result;

  result << std::setprecision(4) << std::fixed << (val * 100.0);
  return result.str();
}
} // namespace float_
} // namespace utils
#endif
