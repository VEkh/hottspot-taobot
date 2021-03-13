#if !defined ETRADE__STOCK_BOT_watch
#define ETRADE__STOCK_BOT_watch

/*
 * ETrade::StockBot
 * POLLING_INTERVAL_SECONDS
 */
#include "stock_bot.h"

#include "fetch_quote.cpp"               // fetch_quote
#include "log_quote.cpp"                 // log_quote
#include "log_simple_moving_average.cpp" // log_simple_moving_average
#include <chrono>                        // std::chrono
#include <thread>                        // std::this_thread

void ETrade::StockBot::watch() {
  while (true) {
    fetch_quote();
    log_quote();
    log_simple_moving_average();

    std::this_thread::sleep_for(
        std::chrono::milliseconds((int)(POLLING_INTERVAL_SECONDS * 1000)));
  }
}

#endif
