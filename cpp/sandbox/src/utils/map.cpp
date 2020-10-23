#if !defined(UTILS_MAP)
#define UTILS_MAP

#include <map>    // std::map
#include <string> // std::string

namespace utils {
namespace map {
std::map<std::string, std::string> merge(std::map<std::string, std::string> a,
                                         std::map<std::string, std::string> b) {
  std::map<std::string, std::string> merged = {};
  std::map<std::string, std::string>::iterator it;

  for (it = a.begin(); it != a.end(); it++) {
    merged[it->first] = it->second;
  }

  for (it = b.begin(); it != b.end(); it++) {
    merged[it->first] = it->second;
  }

  return merged;
}
} // namespace map
} // namespace utils

#endif
