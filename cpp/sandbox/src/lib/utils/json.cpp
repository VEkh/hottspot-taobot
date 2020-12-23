#if !defined UTILS__JSON
#define UTILS__JSON

#include "deps.cpp" // json
#include <vector>   // std::vector

namespace utils {
namespace json {
json slice(json input, std::vector<const char *> keys) {
  json output;

  for (const char *key : keys) {
    output[key] = input[key];
  }

  return output;
}
} // namespace json
} // namespace utils

#endif
