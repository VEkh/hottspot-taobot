#if !defined UTILS__JSON
#define UTILS__JSON

#include "deps.cpp" // nlohmann::json
#include <vector>   // std::vector

namespace utils {
namespace json {
nlohmann::json jslice(const nlohmann::json &input,
                      const std::vector<const char *> keys) {
  nlohmann::json output;

  for (const char *key : keys) {
    output[key] = input[key];
  }

  return output;
}
} // namespace json
} // namespace utils

#endif
