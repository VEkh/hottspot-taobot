#ifndef ALPACA__CLIENT_parse_quote
#define ALPACA__CLIENT_parse_quote

#include "client.h"           // Alpaca::Client, quote_t
#include "deps.cpp"           // json
#include "lib/utils/time.cpp" // ::utils::time_
#include <ctime>              // std::time, std::time_t
#include <string>             // std::string, std::stod

Alpaca::Client::quote_t
Alpaca::Client::parse_quote(const std::string &response_body) {
  json quote_json = json::parse(response_body);

  const double ask = quote_json["quote"]["ap"];
  const double bid = quote_json["quote"]["bp"];
  const double price = (ask + bid) * 0.5;
  const long now = ::utils::time_::epoch("milliseconds");

  quote_t quote;
  quote.ask = ask;
  quote.bid = bid;
  quote.price = price;
  quote.timestamp = now;

  return quote;
}

#endif
