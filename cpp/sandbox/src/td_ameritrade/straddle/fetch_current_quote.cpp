#if !defined TD_AMERITRADE__STRADDLE_fetch_current_quote
#define TD_AMERITRADE__STRADDLE_fetch_current_quote

#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/json.cpp" // utils::json
#include "straddle.h" // TdAmeritrade::Straddle, original_quote, stream_format, symbol, td_ameritrade_client
#include "td_ameritrade/deps.cpp" // json
#include <iostream>               // std::cout, std::endl

#include <string> // std::string
#include <vector> // std::vector

void TdAmeritrade::Straddle::fetch_current_quote() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::string quote_string = td_ameritrade_client.fetch_quote(symbol);

  if (original_quote.empty()) {
    original_quote = json::parse(quote_string)[symbol];
  }

  quote = json::parse(quote_string)[symbol];

  json quote_snapshot =
      utils::json::jslice(quote, {"highPrice", "lastPrice", "lowPrice"});

  std::cout << fmt.bold << fmt.yellow << std::endl;
  std::cout << symbol << " quote: " << quote_snapshot << std::endl;
  std::cout << fmt.reset;
}

#endif
