#ifndef ALPACA__CLIENT_parse_quote
#define ALPACA__CLIENT_parse_quote

#include "client.h"           // Alpaca::Client, quote_t
#include "deps.cpp"           // json
#include "lib/utils/json.cpp" // ::utils::json
#include <ctime>              // std::time, std::time_t
#include <string>             // std::string, std::stod

Alpaca::Client::quote_t
Alpaca::Client::parse_quote(const std::string &response_body) {
  std::time_t now = std::time(nullptr);

  json quote_json = ::utils::json::parse_with_catch(
      response_body, "ALPACA__CLIENT_parse_quote");

  const double price = quote_json["trade"]["p"];

  quote_t quote;
  quote.price = price;
  quote.timestamp = now;

  return quote;
}

#endif
