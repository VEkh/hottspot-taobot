#if !defined ETRADE__OAUTH_HEADER_build_signature_base_string
#define ETRADE__OAUTH_HEADER_build_signature_base_string

#include "build_params_string.cpp"         // build_params_string
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/utils/string.cpp"            // utils::string
#include "lib/utils/uri.cpp"               // utils::uri
#include "oauth_header.h"                  // ETrade::OAuthHeader, props
#include <string>                          // std::string

std::string ETrade::OAuthHeader::build_signature_base_string() {
  std::string base_url = utils::string::split(props.request_url, "?")[0];
  std::string params = build_params_string();
  std::stringstream signature_base_string;

  signature_base_string << CurlClient::method_to_string(props.method) << "&"
                        << utils::uri::percent_encode(base_url) << "&"
                        << utils::uri::percent_encode(params);

  return signature_base_string.str();
}

#endif
