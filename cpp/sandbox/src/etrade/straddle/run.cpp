#if !defined ETRADE__STRADDLE_run
#define ETRADE__STRADDLE_run

#include "fetch_and_set_quote.cpp" // fetch_and_set_quote
#include "lib/formatted.cpp"       // Formatted
#include "open.cpp"                // open
#include "set_order_prices.cpp"    // set_order_prices
#include "straddle.h" // ETrade::Straddle, quantity, stream_format, symbol, etrade_client
#include "watch.cpp" // watch
#include <iostream>  // std::cout, std::endl

void ETrade::Straddle::log_start_message() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << "Straddling " << fmt.blue << quantity << fmt.cyan
            << " share(s) of " << fmt.blue << symbol << std::endl;
  std::cout << fmt.reset;
}

void ETrade::Straddle::run() {
  etrade_client.refresh_token();
  log_start_message();
  fetch_and_set_quote();
  set_order_prices();
  open();
  watch();
}

#endif
