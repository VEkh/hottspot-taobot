#ifndef OANDA__CLIENT_parse_quote
#define OANDA__CLIENT_parse_quote

#include "client.h"           // Oanda::Client, quote_t
#include "deps.cpp"           // json
#include "lib/utils/time.cpp" // ::utils::time_
#include <string>             // std::string, std::stod

Oanda::Client::quote_t
Oanda::Client::parse_quote(const std::string &response_body) {
  json quote_json = json::parse(response_body);

  std::string ask_string = quote_json["candles"][0]["ask"]["c"];
  std::string bid_string = quote_json["candles"][0]["bid"]["c"];
  std::string mid_string = quote_json["candles"][0]["mid"]["c"];
  const double now = ::utils::time_::epoch("nanoseconds") / 1.0e9;

  quote_t quote;
  quote.ask = std::stod(ask_string);
  quote.bid = std::stod(bid_string);
  quote.price = std::stod(mid_string);
  quote.timestamp = now;

  return quote;
}

#endif
