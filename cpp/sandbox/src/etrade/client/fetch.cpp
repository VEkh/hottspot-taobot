#if !defined ETRADE__CLIENT_fetch
#define ETRADE__CLIENT_fetch

#include "build_request_header.cpp"        // build_request_header
#include "client.h"                        // ETrade::Client, oauth
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted::error_message
#include "load_token.cpp"                  // load_token
#include <iostream>                        // std::cout, std::endl
#include <map>                             // std::map
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::stod, std::string

CurlClient ETrade::Client::fetch(char *url) {
  if (url == nullptr) {
    std::string error_message =
        Formatted::error_message("Please provide a url.");

    throw std::invalid_argument(error_message);
  }

  return fetch(std::string(url));
}

CurlClient ETrade::Client::fetch(std::string url) {
  load_token();

  return fetch(url, {
                        {"oauth_token", oauth.token},
                        {"oauth_token_secret", oauth.token_secret},
                    });
}
CurlClient ETrade::Client::fetch(
    std::string url, std::map<std::string, std::string> request_header_params) {
  std::string request_header = build_request_header(url, request_header_params);

  CurlClient::props_t curl_props = {
      .body = "",
      .body_params = {},
      .debug_flag = (CurlClient::debug_t)props.debug_flag,
      .headers = {{"Authorization", request_header}},
      .method = CurlClient::http_method_t::GET,
      .query_params = {},
      .url = url,
  };

  CurlClient curl_client(curl_props);
  curl_client.request();

  return curl_client;
}

#endif
