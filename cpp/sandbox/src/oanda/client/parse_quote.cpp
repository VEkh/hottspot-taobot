#ifndef OANDA__CLIENT_parse_quote
#define OANDA__CLIENT_parse_quote

#include "client.h" // Oanda::Client, quote_t
#include "deps.cpp" // json
#include <string>   // std::string, std::stod
#include <time.h>   // time, time_t

Oanda::Client::quote_t
Oanda::Client::parse_quote(const std::string &response_body) {
  time_t now;
  time(&now);

  json quote_json = json::parse(response_body);
  std::string price_string = quote_json["candles"][0]["mid"]["c"];

  quote_t quote;
  quote.price = std::stod(price_string);
  quote.timestamp = now;

  return quote;
}

#endif
