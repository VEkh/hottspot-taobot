#ifndef OANDA__CLIENT_fetch_quote
#define OANDA__CLIENT_fetch_quote

#include "client.h"                        // Oanda::Client
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

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

  CurlClient curl_client = fetch(request_url);

  return curl_client.response.body;
}

#endif
