#if !defined ETRADE__STRADDLE_fetch_and_set_quote
#define ETRADE__STRADDLE_fetch_and_set_quote

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include "odometer_tick.cpp" // odometer_tick
#include "straddle.h" // ETrade::Straddle, etrade_client, stream_format, symbol
#include <iostream>   // std::cout, std::endl
#include <string>     // std::string

json translate_quote(const std::string &response_body) {
  json input = json::parse(response_body);
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0)["All"];
  json output = {
      {"highPrice", full_quote["high"]},
      {"currentPrice", full_quote["lastTrade"]},
      {"lowPrice", full_quote["low"]},
  };

  return output;
}

void ETrade::Straddle::fetch_and_set_quote() {
  Formatted::fmt_stream_t fmt = stream_format;
  Formatted::Stream quote_color = fmt.yellow;
  std::string quote_string = etrade_client.fetch_quote(symbol);
  json current_quote = translate_quote(quote_string);

  if (!quote.empty()) {
    if (current_quote["currentPrice"] > quote["currentPrice"]) {
      quote_color = fmt.green;
    } else if (current_quote["currentPrice"] < quote["currentPrice"]) {
      quote_color = fmt.red;
    }

  }

  quote = current_quote;

  std::cout << fmt.bold << quote_color << std::endl;
  std::cout << symbol << " quote: " << quote << std::endl;
  std::cout << fmt.reset;
}

#endif
