#if !defined ETRADE__OAUTH_HEADER_build_params_string
#define ETRADE__OAUTH_HEADER_build_params_string

#include "lib/utils/map.cpp"    // utils::map
#include "lib/utils/string.cpp" // utils::string
#include "lib/utils/uri.cpp"    // utils::uri
#include "oauth_header.h"       // ETrade::OAuthHeader, props
#include <any>                  // std::any
#include <map>                  // std::map
#include <sstream>              // std::stringstream
#include <string>               // std::string, std::to_string
#include <vector>               // std::vector

std::map<const char *, std::any> parse_request_url(std::string request_url) {
  std::map<const char *, std::any> result = {
      {"query_params", (std::map<std::string, std::string>){}},
  };

  std::vector<std::string> url_parts = utils::string::split(request_url, "?");

  result["base_url"] = url_parts[0];

  if (url_parts.size() > 1) {
    result["query_params"] = utils::uri::parse_query_params(url_parts[1]);
  }

  return result;
}

std::string ETrade::OAuthHeader::build_params_string() {
  std::stringstream output;
  std::map<std::string, std::string> params = {
      {"oauth_callback",
       utils::uri::percent_encode(props.params["oauth_callback"])},
      {"oauth_consumer_key",
       utils::uri::percent_encode(props.params["oauth_consumer_key"])},
      {"oauth_nonce", nonce},
      {"oauth_signature_method",
       utils::uri::percent_encode(props.params["oauth_signature_method"])},
      {"oauth_timestamp", std::to_string(timestamp)},
      {"oauth_token", props.params["oauth_token"]},
      {"oauth_verifier", props.params["oauth_verifier"]}};

  std::map<const char *, std::any> parsed_request_url =
      parse_request_url(props.request_url);

  std::map<std::string, std::string> query_params =
      std::any_cast<std::map<std::string, std::string>>(
          parsed_request_url["query_params"]);

  params = utils::map::merge(params, query_params);

  std::map<std::string, std::string>::iterator it;
  for (it = params.begin(); it != params.end(); it++) {
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
