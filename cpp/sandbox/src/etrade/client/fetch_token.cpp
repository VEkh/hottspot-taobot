#if !defined ETRADE__CLIENT_fetch_token
#define ETRADE__CLIENT_fetch_token

#include "client.h"  // ETrade::Client, oauth, props, stream_format
#include "fetch.cpp" // fetch
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/formatted.cpp"                      // Formatted
#include <iostream>                               // std::cout, std::endl
#include <regex>                                  // std::regex
#include <string>                                 // std::string

const char *request_action(std::string url) {
  if (std::regex_search(url, std::regex(".*renew.*"))) {
    return "refresh";
  }

  return "fetch";
}

std::string ETrade::Client::fetch_token(std::string request_url) {
  Formatted::fmt_stream_t fmt = stream_format;

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return fetch(request_url,
                     {
                         {"oauth_token", oauth.token},
                         {"oauth_token_secret", oauth.token_secret},
                         {"oauth_verifier", oauth.verifier},
                     });
        ;
      },
      [](const std::string &response_body) -> bool {
        return std::regex_search(
            response_body, std::regex("oauth_parameters_absent=oauth_nonce"));
      });

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
