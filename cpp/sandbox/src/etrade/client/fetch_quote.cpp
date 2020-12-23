#if !defined ETRADE__CLIENT_fetch_quote
#define ETRADE__CLIENT_fetch_quote

#include "client.h"                        // ETrade::Client
#include "etrade/deps.cpp"                 // json
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include <iostream>                        // std::cout, std::endl
#include <map>                             // std::map
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

bool is_valid_response(std::string response_body) {
  json response_json = json::parse(response_body);

  return response_json["QuoteResponse"].contains("QuoteData");
}

void terminate(std::string response_body, std::string symbol) {
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
      "https://api.etrade.com/v1/market/quote/" + symbol + ".json";

  CurlClient curl_client = fetch(request_url);
  std::string response_body = curl_client.response.body;

  if (!is_valid_response(response_body)) {
    terminate(response_body, symbol);
  }

  return response_body;
}

#endif
