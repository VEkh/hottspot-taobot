#ifndef UTILS__JSON
#define UTILS__JSON

#include "deps.cpp"          // nlohmann
#include "lib/formatted.cpp" // Formatted
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string
#include <vector>            // std::vector

namespace utils {
namespace json {
using json_ = nlohmann::json;

json_ jslice(const json_ &input, const std::vector<const char *> keys) {
  json_ output;

  for (const char *key : keys) {
    output[key] = input[key];
  }

  return output;
}

json_ parse_with_catch(const std::string &input, const char *process_name) {
  try {
    return json_::parse(input);
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string(process_name) + ": Error while parsing: " + input);

    throw(std::invalid_argument(error_message));
  }
}
} // namespace json
} // namespace utils

#endif
