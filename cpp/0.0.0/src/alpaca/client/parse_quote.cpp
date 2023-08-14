#ifndef ALPACA__CLIENT_parse_quote
#define ALPACA__CLIENT_parse_quote

#include "client.h"           // Alpaca::Client, quote_t
#include "deps.cpp"           // json
#include "lib/utils/time.cpp" // ::utils::time_
#include <string>             // std::string, std::stod

Alpaca::Client::quote_t
Alpaca::Client::parse_quote(const std::string &response_body) {
  json quote_json = json::parse(response_body);

  const double ask = quote_json["quote"]["ap"];
  const double bid = quote_json["quote"]["bp"];
  const double price = (ask + bid) * 0.5;

  // The quote's timestamp at "t" is sometimes wildly inaccurate, so you'll
  // have to settle for the system's current time.
  const double now = ::utils::time_::epoch("nanoseconds") / 1.0e9;

  quote_t quote;
  quote.ask = ask;
  quote.bid = bid;
  quote.price = price;
  quote.timestamp = now;

  return quote;
}

#endif
