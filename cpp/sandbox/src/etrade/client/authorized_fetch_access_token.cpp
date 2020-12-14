#if !defined ETRADE__CLIENT_authorized_fetch_access_token
#define ETRADE__CLIENT_authorized_fetch_access_token

#include "build_request_header.cpp" // build_request_header
#include "client.h"                 // ETrade::Client, props, stream_format
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/uri.cpp"               // utils::uri
#include "write_response_to_file.cpp"      // write_response_to_file
#include <iostream>                        // std::cout, std::endl
#include <map>                             // std::map
#include <string>                          // std::string

void ETrade::Client::authorized_fetch_access_token() {
  Formatted::fmt_stream_t fmt = stream_format;
  std::string request_url = "https://api.etrade.com/oauth/access_token";
  std::string request_header = build_request_header(
      request_url, {
                       {"oauth_token", client_config.oauth_token},
                       {"oauth_token_secret", client_config.oauth_token_secret},
                       {"oauth_verifier", client_config.oauth_verifier},
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

  std::string response_body = curl_client.response.body;

  if (curl_client.is_xml_response()) {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout << "❌ Failed to fetch request token: " << std::endl;
    std::cout << response_body << std::endl;
    std::cout << fmt.reset << std::endl;

    exit(1);
  }

  std::cout << fmt.bold << fmt.green;
  std::cout << "✅ Successfully fetched access token." << std::endl;
  std::cout << fmt.reset;

  if (props.debug_flag == debug_t::ON) {
    std::cout << fmt.bold << fmt.yellow << std::endl;
    std::cout << response_body << std::endl;
    std::cout << "Writing to: " << TOKENS_PATH << std::endl;
    std::cout << fmt.reset;
  }

  std::map<std::string, std::string> parsed_tokens =
      utils::uri::parse_query_params(response_body);

  json tokens_json;
  tokens_json["oauth_token"] = parsed_tokens["oauth_token"];
  tokens_json["oauth_token_secret"] = parsed_tokens["oauth_token_secret"];

  write_response_to_file(tokens_json.dump(2), TOKENS_PATH);
}

#endif
