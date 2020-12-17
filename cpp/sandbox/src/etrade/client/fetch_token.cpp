#if !defined ETRADE__CLIENT_fetch_token
#define ETRADE__CLIENT_fetch_token

#include "build_request_header.cpp" // build_request_header
#include "client.h"                 // ETrade::Client, props, stream_format
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/string.cpp"            // utils::string
#include "lib/utils/uri.cpp"               // utils::uri
#include <iostream>                        // std::cout, std::endl
#include <regex>                           // std::regex
#include <string>                          // std::string

const char *request_action(std::string url) {
  if (std::regex_search(url, std::regex(".*renew.*"))) {
    return "refresh";
  }

  return "fetch";
}

std::string ETrade::Client::fetch_token(std::string request_url) {
  Formatted::fmt_stream_t fmt = stream_format;
  std::string request_header = build_request_header(
      request_url, {
                       {"oauth_token", oauth.token},
                       {"oauth_token_secret", oauth.token_secret},
                       {"oauth_verifier", oauth.verifier},
                   });

  CurlClient::props_t curl_props = {
      .body = "",
      .body_params = {},
      .debug_flag = (CurlClient::debug_t)props.debug_flag,
      .headers = {{"Authorization", request_header}},
      .method = CurlClient::http_method_t::GET,
      .query_params = {},
      .url = request_url,
  };

  CurlClient curl_client(curl_props);
  curl_client.request();

  const char *action = request_action(request_url);
  std::string response_body = curl_client.response.body;

  if (curl_client.is_xml_response()) {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout << "❌ Failed to " << action << " access token: " << std::endl;
    std::cout << response_body << std::endl;
    std::cout << fmt.reset << std::endl;

    exit(1);
  }

  std::cout << fmt.bold << fmt.green;
  std::cout << "✅ Successfully " << action << "ed access token." << std::endl;
  std::cout << fmt.reset;

  return response_body;
}

#endif
