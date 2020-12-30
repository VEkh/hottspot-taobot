#if !defined ETRADE__STRADDLE_watch
#define ETRADE__STRADDLE_watch

#include "fetch_and_set_orders.cpp" // fetch_and_set_orders
#include "fetch_and_set_quote.cpp"  // fetch_and_set_quote
#include "lib/formatted.cpp"        // Formatted
#include "status.cpp"               // status
#include "straddle.h"               // ETrade::Straddle, stream_format, symbol
#include "watch_buy_positions.cpp"  // watch_buy_positions
#include <chrono>                   // std::chrono
#include <iostream>                 // std::cout, std::endl
#include <thread>                   // std::this_thread

void ETrade::Straddle::watch() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.yellow << std::endl;

  while (status() != status_t::CLOSED) {
    fetch_and_set_quote();
    fetch_and_set_orders();
    watch_buy_positions();

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  std::cout << fmt.reset;
}

#endif
