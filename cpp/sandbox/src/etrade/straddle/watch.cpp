#if !defined ETRADE__STRADDLE_watch
#define ETRADE__STRADDLE_watch

/*
 * ETrade::Straddle
 * POLLING_INTERVAL_SECONDS
 * speedometer
 * stream_format
 * symbol
 */
#include "straddle.h"

#include "fetch_and_set_orders.cpp" // fetch_and_set_orders
#include "fetch_and_set_quote.cpp"  // fetch_and_set_quote
#include "lib/formatted.cpp"        // Formatted
#include "log_prices.cpp"           // log_prices
#include "log_status.cpp"           // log_status
#include "status.cpp"               // status
#include "watch_buy.cpp"            // watch_buy
#include "watch_sell_short.cpp"     // watch_sell_short
#include <chrono>                   // std::chrono
#include <iostream>                 // std::cout, std::endl
#include <thread>                   // std::this_thread

void ETrade::Straddle::watch() {
  Formatted::fmt_stream_t fmt = stream_format;
  log_prices();

  while (status() != status_t::CLOSED) {
    fetch_and_set_quote();
    fetch_and_set_orders();
    speedometer.log();
    log_prices();
    watch_buy();
    watch_sell_short();
    log_status();

    std::this_thread::sleep_for(std::chrono::seconds(POLLING_INTERVAL_SECONDS));
  }

  log_prices();
  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << "👋🏾 Completed straddling " << fmt.blue << quantity
            << fmt.cyan << " share(s) of " << fmt.blue << symbol << std::endl;
  std::cout << fmt.reset;
}

#endif
