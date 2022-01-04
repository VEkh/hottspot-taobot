#ifndef ALPACA__CLIENT_fetch_quote
#define ALPACA__CLIENT_fetch_quote

#include "client.h"                        // Alpaca::Client
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

std::string Alpaca::Client::fetch_quote(char *symbol) {
  if (symbol == nullptr) {
    std::string error_message =
        Formatted::error_message("Please provide a stock symbol.");

    throw std::invalid_argument(error_message);
  }

  return fetch_quote(std::string(symbol));
}

std::string Alpaca::Client::fetch_quote(const std::string &symbol) {
  std::string request_url =
      config.data_base_url + "/v2/stocks/" + symbol + "/trades/latest";

  CurlClient curl_client = fetch(request_url);

  return curl_client.response.body;
}

#endif
