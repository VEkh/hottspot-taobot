#if !defined ETRADE__STOCK_BOT_run
#define ETRADE__STOCK_BOT_run

#include "fetch_and_set_quote.cpp" // fetch_and_set_quote
#include "lib/formatted.cpp"       // Formatted
#include "set_order_prices.cpp"    // set_order_prices
#include "stock_bot.h" // ETrade::StockBot, quantity, stream_format, symbol
#include "watch.cpp"   // watch
#include <iostream>    // std::cout, std::endl

void ETrade::StockBot::log_start_message() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << "Straddling " << fmt.blue << quantity << fmt.cyan
            << " share(s) of " << fmt.blue << symbol << std::endl;
  std::cout << fmt.reset;
}

void ETrade::StockBot::run() {
  log_start_message();
  fetch_and_set_quote();
  set_order_prices();
  watch();
}

#endif
