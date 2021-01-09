#if !defined ETRADE__STRADDLE_fetch_and_set_quote
#define ETRADE__STRADDLE_fetch_and_set_quote

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include "straddle.h" // ETrade::Straddle, etrade_client, original_quote, stream_format, symbol
#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <vector>   // std::vector

json translate_quote(const std::string &response_body) {
  json input = json::parse(response_body);
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0)["All"];
  json output = {
      {"highPrice", full_quote["high"]},
      {"lastPrice", full_quote["lastTrade"]},
      {"lowPrice", full_quote["low"]},
  };

  return output;
}

void ETrade::Straddle::fetch_and_set_quote() {
  Formatted::fmt_stream_t fmt = stream_format;
  Formatted::Stream quote_color = fmt.yellow;
  std::string quote_string = etrade_client.fetch_quote(symbol);
  json translated_quote = translate_quote(quote_string);

  if (!quote.empty()) {
    if (translated_quote["lastPrice"] > quote["lastPrice"]) {
      quote_color = fmt.green;
    } else if (translated_quote["lastPrice"] < quote["lastPrice"]) {
      quote_color = fmt.red;
    }
  }

  if (original_quote.empty()) {
    original_quote = translated_quote;
  }

  quote = translated_quote;

  std::cout << fmt.bold << quote_color << std::endl;
  std::cout << symbol << " quote: " << quote << std::endl;
  std::cout << fmt.reset;
}

#endif
