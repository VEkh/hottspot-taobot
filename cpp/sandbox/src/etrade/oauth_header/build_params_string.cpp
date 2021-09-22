#if !defined ETRADE__OAUTH_HEADER_build_params_string
#define ETRADE__OAUTH_HEADER_build_params_string

#include "lib/utils/map.cpp"    // utils::map
#include "lib/utils/string.cpp" // utils::string
#include "lib/utils/uri.cpp"    // utils::uri
#include "oauth_header.h"       // ETrade::OAuthHeader, params, props
#include <any>                  // std::any
#include <map>                  // std::map
#include <sstream>              // std::stringstream
#include <string>               // std::string, std::to_string
#include <vector>               // std::vector

std::map<const char *, std::any> parse_request_url(std::string request_url) {
  std::map<const char *, std::any> result = {
      {"query_params", (std::map<std::string, std::string>){}},
  };

  std::vector<std::string> url_parts = ::utils::string::split(request_url, "?");

  result["base_url"] = url_parts[0];

  if (url_parts.size() > 1) {
    result["query_params"] = ::utils::uri::parse_query_params(url_parts[1]);
  }

  return result;
}

std::string ETrade::OAuthHeader::build_params_string() {
  std::stringstream output;

  std::map<const char *, std::any> parsed_request_url =
      parse_request_url(props.request_url);

  std::map<std::string, std::string> query_params =
      std::any_cast<std::map<std::string, std::string>>(
          parsed_request_url["query_params"]);

  std::map<std::string, std::string> signature_params =
      ::utils::map::merge(params, query_params);

  std::map<std::string, std::string>::iterator it;
  for (it = signature_params.begin(); it != signature_params.end(); it++) {
    std::string value = it->second;

    if (value.empty()) {
      continue;
    }

    if (!output.str().empty()) {
      output << "&";
    }

    output << it->first << "=" << value;
  }

  return output.str();
}

#endif
