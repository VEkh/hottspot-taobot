#ifndef OANDA__CLIENT_fetch_quote
#define OANDA__CLIENT_fetch_quote

#include "client.h"                               // Oanda::Client
#include "fetch.cpp"                              // fetch
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/formatted.cpp"                      // Formatted
#include <regex>     // std::regex, std::regex_search
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

namespace Oanda {
namespace fetch_quote {
bool is_retriable_response(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  if (response_body.empty()) {
    return true;
  }

  return std::regex_search(response_body, std::regex("<html>"));
}
} // namespace fetch_quote
} // namespace Oanda

std::string Oanda::Client::fetch_quote(char *symbol) {
  if (symbol == nullptr) {
    std::string error_message =
        Formatted::error_message("Please provide a stock symbol.");

    throw std::invalid_argument(error_message);
  }

  return fetch_quote(std::string(symbol));
}

std::string Oanda::Client::fetch_quote(std::string symbol) {
  std::string request_url = config.base_url + "/v3/instruments/" + symbol +
                            "/candles?count=1&price=BAM";

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient { return fetch(request_url); },
      Oanda::fetch_quote::is_retriable_response);

  return curl_client.response.body;
}

#endif
