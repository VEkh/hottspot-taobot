#if !defined(UTILS_FLOAT)
#define UTILS_FLOAT

#include <iomanip> // std::setprecision
#include <sstream> // std::stringstream
#include <string>  // std::stof, std::string

namespace utils {
namespace float_ {
std::string toCurrency(float val) {
  std::stringstream result;

  result << std::setprecision(2) << std::fixed << val;
  return result.str();
}

std::string toRoundedPercentage(float val) {
  std::stringstream result;

  result << std::setprecision(4) << std::fixed << (val * 100.0);
  return result.str();
}
} // namespace float_
} // namespace utils
#endif
