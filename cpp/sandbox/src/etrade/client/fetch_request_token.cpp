#if !defined ETRADE__CLIENT_fetch_request_token
#define ETRADE__CLIENT_fetch_request_token

#include "build_request_header.cpp" // build_request_header
#include "client.h"                 // ETrade::Client, props, stream_format
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/utils/uri.cpp"               // utils::uri
#include <iostream>                        // std::cout, std::endl
#include <map>                             // std::map
#include <regex>                           // std::regex, std::regex_search
#include <string>                          // std::string

bool is_xml_response(std::map<std::string, std::string> headers) {
  return std::regex_search(headers["Content-Type"], std::regex("text\\/html"));
}

void ETrade::Client::fetch_request_token() {
  Formatted::fmt_stream_t fmt = stream_format;
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

  std::string response_body = curl_client.response.body;

  if (is_xml_response(curl_client.response.headers)) {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout << "Failed to fetch request token: " << std::endl;
    std::cout << response_body << std::endl;
    std::cout << fmt.reset << std::endl;

    exit(1);
  }

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "Successfully fetched request token: " << std::endl;
  std::cout << fmt.yellow;
  std::cout << response_body << std::endl;
  std::cout << fmt.reset;

  std::map<std::string, std::string> parsed_tokens =
      utils::uri::parse_query_params(response_body);

  client_config.oauth_token = parsed_tokens["oauth_token"];
  client_config.oauth_token_secret = parsed_tokens["oauth_token_secret"];
}

#endif
