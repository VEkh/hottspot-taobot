#if !defined ETRADE__CLIENT_fetch_request_token
#define ETRADE__CLIENT_fetch_request_token

#include "build_request_header.cpp" // build_request_header
#include "client.h"                 // ETrade::Client, props
#include "lib/curl_client/curl_client.cpp"      // CurlClient
#include "lib/utils/debug.cpp"      // utils::debug::inspect
#include <string>                   // std::string

std::string ETrade::Client::fetch_request_token() {
  std::string request_url = "https://api.etrade.com/oauth/request_token";

  std::string request_header = build_request_header(request_url, {});

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

  std::string request_token = curl_client.response.body;
  utils::debug::inspect(curl_client.response.headers);

  return request_token;
}

#endif
