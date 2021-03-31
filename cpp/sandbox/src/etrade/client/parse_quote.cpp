#if !defined ETRADE__CLIENT_parse_quote
#define ETRADE__CLIENT_parse_quote

/*
 * ETrade::Client
 * quote_t
 */
#include "client.h"

#include "etrade/deps.cpp"  // json
#include "etrade/types.cpp" // ETrade::t
#include <string>           // std::string
#include <time.h>           // time, time_t

ETrade::t::quote_t
ETrade::Client::parse_quote(const std::string &response_body) {
  time_t now;
  time(&now);

  json input = json::parse(response_body);
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0);
  std::string symbol = full_quote["Product"]["symbol"];

  quote_t quote;
  quote.current_price = full_quote["All"]["lastTrade"];
  quote.high = full_quote["All"]["high"];
  quote.low = full_quote["All"]["low"];
  quote.symbol = (char *)symbol.c_str();
  quote.timestamp = now;

  return quote;
}

#endif
