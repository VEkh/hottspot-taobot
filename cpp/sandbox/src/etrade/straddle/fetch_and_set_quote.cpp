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
  std::string quote_string = etrade_client.fetch_quote(symbol);
  json translated_quote = translate_quote(quote_string);

  quote = translated_quote;

  if (original_quote.empty()) {
    original_quote = translated_quote;
  }

  std::cout << fmt.bold << fmt.yellow << std::endl;
  std::cout << symbol << " quote: " << quote << std::endl;
  std::cout << fmt.reset;
}

#endif
