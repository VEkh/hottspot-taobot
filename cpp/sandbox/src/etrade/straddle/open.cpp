#if !defined ETRADE__STRADDLE_open
#define ETRADE__STRADDLE_open

#include "lib/formatted.cpp" // Formatted
#include "log_prices.cpp"    // log_prices
#include "straddle.h"        // ETrade::Straddle, etrade_client, stream_format
#include <iostream>          // std::cout, std::endl

void ETrade::Straddle::open() {
  Formatted::fmt_stream_t fmt = stream_format;

  log_prices();
  etrade_client.place_order(sell_short_open_order);
  etrade_client.place_order(buy_open_order);

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "✅ Straddle successfully opened!" << std::endl;
  std::cout << fmt.reset;
}

#endif
