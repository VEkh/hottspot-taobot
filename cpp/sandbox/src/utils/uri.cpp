#if !defined(UTILS_URI)
#define UTILS_URI

#include "string.cpp"  // utils::string::split
#include <curl/curl.h> // curl_easy_escape, curl_free, curl_easy_init
#include <map>         // std::map
#include <sstream>     // std::stringstream
#include <string.h>    // strlen
#include <string>      // std::string
#include <vector>      // std::vector

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

std::string percentDecode(const char *str) {
  if (str == NULL) {
    return "";
  }

  CURL *curl = curl_easy_init();
  int output_length;
  const char *unescaped =
      curl_easy_unescape(curl, str, strlen(str), &output_length);

  return (std::string)unescaped;
}

std::string percentDecode(std::string str) {
  return percentDecode(str.c_str());
}

std::string percentEncode(const char *str) {
  if (str == NULL) {
    return "";
  }

  CURL *curl = curl_easy_init();
  char *escaped = curl_easy_escape(curl, str, strlen(str));
  std::string result = (std::string)escaped;

  curl_free(escaped);

  return result;
}

std::string percentEncode(std::string str) {
  return percentEncode(str.c_str());
}

std::string buildQueryParams(std::map<std::string, std::string> params) {
  std::stringstream output;

  output << "?";

  std::map<std::string, std::string>::iterator it;
  for (it = params.begin(); it != params.end(); it++) {
    if (it != params.begin()) {
      output << "&";
    }

    output << it->first << "=" << percentEncode(it->second);
  }

  return output.str();
}

} // namespace uri
} // namespace utils
#endif
