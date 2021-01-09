#if !defined ETRADE__CLIENT_fetch_quote
#define ETRADE__CLIENT_fetch_quote

#include "client.h"                        // ETrade::Client, client_config
#include "etrade/deps.cpp"                 // json
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/formatted.cpp"                      // Formatted
#include <iostream>                               // std::cout, std::endl
#include <map>                                    // std::map
#include <regex>     // std::regex, std::regex_search
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

namespace ETrade {
namespace fetch_quote {
bool is_retriable_response(const std::string &response_body) {
  if (response_body.empty()) {
    return true;
  }

  json response = json::parse(response_body);

  if (response["QuoteResponse"].contains("Messages") &&
      response["QuoteResponse"]["Messages"]["Message"][0]["code"] == 1002) {
    return true;
  }

  if (std::regex_search(response_body,
                        std::regex("oauth_parameters_absent=oauth_nonce"))) {
    return true;
  }

  if (std::regex_search(response_body,
                        std::regex("oauth_problem=nonce_used"))) {
    return true;
  }

  return false;
}
} // namespace fetch_quote
} // namespace ETrade

bool is_valid_response(const std::string &response_body) {
  json response = json::parse(response_body);

  return response["QuoteResponse"].contains("QuoteData");
}

void terminate(const std::string &response_body, const std::string &symbol) {
  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red << std::endl;
  std::cout << "❌ There was a problem fetching <" << symbol
            << ">'s quote. Here's the response:" << std::endl;
  std::cout << response_body << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

std::string ETrade::Client::fetch_quote(char *symbol) {
  if (symbol == nullptr) {
    std::string error_message =
        Formatted::error_message("Please provide a stock symbol.");

    throw std::invalid_argument(error_message);
  }

  return fetch_quote(std::string(symbol));
}

std::string ETrade::Client::fetch_quote(std::string symbol) {
  std::string request_url =
      client_config.base_url + "/v1/market/quote/" + symbol + ".json";

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient { return fetch(request_url); },
      ETrade::fetch_quote::is_retriable_response);

  std::string response_body = curl_client.response.body;

  if (!is_valid_response(response_body)) {
    terminate(response_body, symbol);
  }

  return response_body;
}

#endif
