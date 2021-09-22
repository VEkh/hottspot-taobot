#if !defined ETRADE__CLIENT_fetch_request_token
#define ETRADE__CLIENT_fetch_request_token

#include "client.h"  // ETrade::Client, config, props, stream_format
#include "fetch.cpp" // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/uri.cpp"               // utils::uri
#include <iostream>                        // std::cout, std::endl
#include <map>                             // std::map
#include <string>                          // std::string

void ETrade::Client::fetch_request_token() {
  Formatted::fmt_stream_t fmt = stream_format;
  CurlClient curl_client =
      fetch(config.base_url + "/oauth/request_token", {});

  std::string response_body = curl_client.response.body;

  if (curl_client.is_xml_response()) {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout << "❌ Failed to fetch request token: " << std::endl;
    std::cout << response_body << std::endl;
    std::cout << fmt.reset << std::endl;

    exit(1);
  }

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "✅ Successfully fetched request token." << std::endl;
  std::cout << fmt.reset;

  if (props.debug_flag == debug_t::ON) {
    std::cout << fmt.bold << fmt.yellow;
    std::cout << response_body << std::endl;
    std::cout << fmt.reset;
  }

  std::map<std::string, std::string> parsed_tokens =
      ::utils::uri::parse_query_params(response_body);

  oauth.token = parsed_tokens["oauth_token"];
  oauth.token_secret = parsed_tokens["oauth_token_secret"];
}

#endif
