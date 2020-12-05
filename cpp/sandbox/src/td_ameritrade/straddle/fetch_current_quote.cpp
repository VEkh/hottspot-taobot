#if !defined TD_AMERITRADE__STRADDLE_fetch_current_quote
#define TD_AMERITRADE__STRADDLE_fetch_current_quote

#include "lib/formatted.cpp" // Formatted
#include "straddle.h" // TdAmeritrade::Straddle, stream_format, symbol, td_ameritrade_client
#include "td_ameritrade/deps.cpp" // json
#include <iostream>               // std::cout, std::endl

#include <string> // std::string
#include <vector> // std::vector

json slice(json input, std::vector<const char *> keys) {
  json output;

  for (const char *key : keys) {
    output[key] = input[key];
  }

  return output;
}

void TdAmeritrade::Straddle::fetch_current_quote() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::string quote_string = td_ameritrade_client.get_quote(symbol);

  quote = json::parse(quote_string)[symbol];
  json condensed_quote = slice(quote, {"highPrice", "lastPrice", "lowPrice"});

  std::cout << fmt.bold << fmt.yellow << symbol << " quote: " << condensed_quote
            << fmt.reset << std::endl;
}

#endif
