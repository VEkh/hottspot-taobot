#if !defined(UTILS_URI)
#define UTILS_URI

#include "string.cpp" // utils::string::split
#include <map>        // std::map
#include <string>     // std::string
#include <vector>     // std::vector

namespace utils {
namespace uri {

std::map<std::string, std::string> parseQueryParams(std::string query_string) {
  if (query_string.empty()) {
    return (std::map<std::string, std::string>){};
  }

  std::map<std::string, std::string> query_params = {};

  std::vector<std::string> query_params_array =
      utils::string::split(query_string, "&");

  std::vector<std::string>::iterator it;
  for (it = query_params_array.begin(); it != query_params_array.end(); it++) {
    std::vector<std::string> param_parts = utils::string::split(*it, "=");

    if (param_parts.size() > 1) {
      query_params[param_parts[0]] = param_parts[1];
    }
  }

  return query_params;
}

} // namespace uri
} // namespace utils
#endif
