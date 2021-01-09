#if !defined ETRADE__STRADDLE_watch
#define ETRADE__STRADDLE_watch

#include "fetch_and_set_orders.cpp" // fetch_and_set_orders
#include "fetch_and_set_quote.cpp"  // fetch_and_set_quote
#include "lib/formatted.cpp"        // Formatted
#include "log_order_statuses.cpp"   // log_order_statuses
#include "log_prices.cpp"           // log_prices
#include "status.cpp"               // status
#include "straddle.h"               // ETrade::Straddle, stream_format, symbol
#include "watch_buy.cpp"            // watch_buy
#include "watch_sell_short.cpp"     // watch_sell_short
#include <chrono>                   // std::chrono
#include <iostream>                 // std::cout, std::endl
#include <thread>                   // std::this_thread

void ETrade::Straddle::watch() {
  Formatted::fmt_stream_t fmt = stream_format;

  while (status() != status_t::CLOSED) {
    fetch_and_set_quote();
    fetch_and_set_orders();
    log_prices();
    log_order_statuses();
    watch_buy();
    watch_sell_short();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << "👋🏾 Completed straddling " << fmt.blue << quantity
            << fmt.cyan << " share(s) of " << fmt.blue << symbol << std::endl;
  std::cout << fmt.reset;
}

#endif
