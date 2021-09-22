#if !defined CURL_CLIENT_to_string
#define CURL_CLIENT_to_string

#include "curl_client.h"        // CurlClient, transformed_props
#include "lib/utils/vector.cpp" // utils::vector::join
#include <string>               // std::string
#include <vector>               // std::vector

std::string CurlClient::to_string() {
  std::vector<std::string> request_parts = {
      "curl",
      "-X" + transformed_props.method,
      transformed_props.headers,
  };

  if (!transformed_props.body.empty()) {
    request_parts.push_back("--data '" + transformed_props.body + "'");
  }

  request_parts.push_back("\"" + transformed_props.url + "\"");

  std::vector<std::string> filtered_request_parts = ::utils::vector::filter(
      request_parts, [](std::string part) -> bool { return !part.empty(); });

  return ::utils::vector::join(filtered_request_parts, " ");
}

#endif
