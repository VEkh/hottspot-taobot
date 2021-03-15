#if !defined ETRADE__STOCK_BOT_watch
#define ETRADE__STOCK_BOT_watch

/*
 * ETrade::StockBot
 * POLLING_INTERVAL_SECONDS
 */
#include "stock_bot.h"

#include "close_position.cpp"            // close_position
#include "fetch_orders.cpp"              // fetch_orders
#include "fetch_quote.cpp"               // fetch_quote
#include "log_open_position.cpp"         // log_open_position
#include "log_quote.cpp"                 // log_quote
#include "log_simple_moving_average.cpp" // log_simple_moving_average
#include "open_position.cpp"             // open_position
#include "set_open_position_prices.cpp"  // set_open_position_prices
#include "set_position_status.cpp"       // set_order_statuses
#include <chrono>                        // std::chrono
#include <thread>                        // std::this_thread

void ETrade::StockBot::watch() {
  while (true) {
    fetch_quote();

    log_quote();
    log_simple_moving_average();
    log_open_position();

    fetch_orders();
    set_position_status();
    open_position();
    set_open_position_prices();
    close_position();

    std::this_thread::sleep_for(
        std::chrono::milliseconds((int)(POLLING_INTERVAL_SECONDS * 1000)));
  }
}

#endif
