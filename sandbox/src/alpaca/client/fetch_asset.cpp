#ifndef ALPACA__CLIENT_fetch_asset
#define ALPACA__CLIENT_fetch_asset

#include "client.h"                               // Alpaca::Client
#include "fetch.cpp"                              // fetch
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/formatted.cpp"                      // Formatted
#include <stdexcept>                              // std::invalid_argument
#include <string>                                 // std::string

namespace Alpaca {
namespace fetch_asset {
bool is_retriable_response(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  return response_body.empty();
}
} // namespace fetch_asset
} // namespace Alpaca

std::string Alpaca::Client::fetch_asset(const std::string &symbol) {
  if (symbol.empty()) {
    std::string error_message =
        Formatted::error_message("Please provide a stock symbol.");

    throw std::invalid_argument(error_message);
  }

  std::string request_url = config.base_url + "/v2/assets/" + symbol;

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return fetch({.timeout_seconds = 3, .url = request_url});
      },
      Alpaca::fetch_asset::is_retriable_response);

  return curl_client.response.body;
}

#endif
