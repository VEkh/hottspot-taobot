#if !defined CURL_CLIENT_write_response_headers
#define CURL_CLIENT_write_response_headers

#include "curl_client.h" // CurlClient, response_t
#include <string>        // std::string
#include <vector>        // std::vector

/*
 * std::cmatch
 * std::regex
 * std::regex_constants
 * std::regex_search
 */
#include <regex>

std::vector<std::string> extract_header_pair(const char *header) {
  std::regex key_value_regex("(.*):\\s(.*)");
  std::cmatch match;

  std::regex_search(header, match, key_value_regex);

  if (match.size() == 3) {
    return {std::string(match[1]), std::string(match[2])};
  }

  std::regex status_regex(".*http\\/\\d\\.\\d\\s(\\d+).*",
                          std::regex_constants::icase);

  std::regex_search(header, match, status_regex);

  if (match.size() == 2) {
    return {"Status", std::string(match[1])};
  }

  return {};
}

size_t CurlClient::write_response_headers(char *buffer, size_t size,
                                          size_t data_size, void *userdata) {
  size_t real_size = size * data_size;
  response_t *res = (response_t *)userdata;

  std::vector<std::string> pair = extract_header_pair(buffer);

  if (pair.size() == 2) {
    res->headers[pair[0]] = pair[1];
  }

  return real_size;
}

#endif
