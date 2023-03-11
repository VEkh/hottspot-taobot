#ifndef UTILS__VECTOR
#define UTILS__VECTOR

#include <string> // std::string
#include <vector> // std::vector

namespace utils {
namespace vector {
std::vector<std::string> filter(std::vector<std::string> collection,
                                bool predicate(std::string)) {
  std::vector<std::string> result;

  for (std::string item : collection) {
    if (predicate(item)) {
      result.push_back(item);
    }
  }

  return result;
}

std::string join(std::vector<std::string> collection,
                 const char *delimiter = ", ") {
  std::string output;
  std::vector<std::string>::iterator it;

  for (it = collection.begin(); it != collection.end(); it++) {
    if (it != collection.begin()) {
      output += delimiter;
    }

    output += *it;
  }

  return output;
}
} // namespace vector
} // namespace utils

#endif
