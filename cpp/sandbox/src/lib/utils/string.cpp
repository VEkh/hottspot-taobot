#ifndef UTILS__STRING
#define UTILS__STRING

#include <algorithm> // std::max, std::replace, std::transform
#include <cctype>    // std::isspace, tolower, toupper
#include <cstring>   // strlen
#include <string>    // std::string
#include <vector>    // std::vector

namespace utils {
namespace string {
std::string downcase(std::string in) {
  std::string out;

  for (char c : in) {
    out += tolower(c);
  }

  return out;
}

std::string ltrim(std::string in) {
  bool nonspace_found = false;
  std::string out;
  std::string::iterator i;
  i = in.begin();

  while (i != in.end()) {
    if (std::isspace(*i)) {
      if (nonspace_found) {
        out += *i;
      }
    } else {
      out += *i;

      if (!nonspace_found) {
        nonspace_found = true;
      }
    }

    i++;
  }

  return out;
}

std::string rtrim(std::string in) {
  bool nonspace_found = false;
  std::string out;
  std::string::reverse_iterator i;
  i = in.rbegin();

  while (i != in.rend()) {
    if (std::isspace(*i)) {
      if (nonspace_found) {
        out = *i + out;
      }
    } else {
      out = *i + out;

      if (!nonspace_found) {
        nonspace_found = true;
      }
    }

    i++;
  }

  return out;
}

std::vector<std::string> split(std::string input, const char *delimiter) {
  std::string match;
  std::string suffix = input;
  std::vector<std::string> result;

  int match_start = 0;
  int match_position = suffix.find(delimiter);

  while (match_position != -1 && suffix != "") {
    if (std::string(delimiter) == "") {
      match = suffix.substr(0, match_position ? match_position : 1);
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

std::string trim(std::string in) {
  std::string out = ltrim(in);
  return rtrim(out);
}

std::string upcase(const std::string &in) {
  std::string out;

  for (char c : in) {
    out += toupper(c);
  }

  return out;
}
} // namespace string
} // namespace utils
#endif
