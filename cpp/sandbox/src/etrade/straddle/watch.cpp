#if !defined ETRADE__STRADDLE_watch
#define ETRADE__STRADDLE_watch

#include "fetch_orders.cpp"        // fetch_orders
#include "lib/formatted.cpp"       // Formatted
#include "set_current_quote.cpp"   // set_current_quote
#include "status.cpp"              // status
#include "straddle.h"              // ETrade::Straddle, stream_format, symbol
#include "watch_buy_positions.cpp" // watch_buy_positions
#include <chrono>                  // std::chrono
#include <iostream>                // std::cout, std::endl
#include <thread>                  // std::this_thread

void ETrade::Straddle::watch() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.yellow << std::endl;

  while (status() != status_t::CLOSED) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    set_current_quote();
    fetch_orders();
    watch_buy_positions();
  }

  std::cout << fmt.reset;
}

#endif
