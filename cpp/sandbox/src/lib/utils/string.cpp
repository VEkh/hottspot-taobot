#if !defined UTILS__STRING
#define UTILS__STRING

#include <algorithm> // std::max, std::replace
#include <cstring>   // strlen
#include <string>    // std::string
#include <vector>    // std::vector

namespace utils {
namespace string {
std::vector<std::string> split(std::string input, const char *delimiter) {
  std::string match;
  std::string suffix = input;
  std::vector<std::string> result;

  int match_start = 0;
  int match_position = suffix.find(delimiter);

  while (match_position != -1 && suffix != "") {
    if (delimiter == "") {
      match = suffix.substr(0, match_position || 1);
    } else {
      match = suffix.substr(0, match_position);
    }

    result.push_back(match);

    int advance_by = std::max((int)strlen(delimiter), 1);

    suffix = suffix.substr(match_position + advance_by, suffix.size() - 1);
    match_position = suffix.find(delimiter);
  }

  result.push_back(suffix);

  return result;
}

std::string stripCommas(std::string input) {
  int position = input.find(",");

  while (position != -1) {
    input.erase(position, 1);
    position = input.find(",");
  }

  return input;
}
} // namespace string
} // namespace utils
#endif
