#if !defined ETRADE__STOCK_BOT_watch
#define ETRADE__STOCK_BOT_watch

/*
 * ETrade::StockBot
 * POLLING_INTERVAL_SECONDS
 */
#include "stock_bot.h"

#include "close_position.cpp"               // close_position
#include "fetch_orders.cpp"                 // fetch_orders
#include "fetch_quote.cpp"                  // fetch_quote
#include "log_moving_price_range.cpp"       // log_moving_price_range
#include "log_position.cpp"                 // log_position
#include "log_position_results.cpp"         // log_position_results
#include "log_quote.cpp"                    // log_quote
#include "log_simple_moving_average.cpp"    // log_simple_moving_average
#include "open_position.cpp"                // open_position
#include "reset_position.cpp"               // reset_position
#include "set_movement_moving_averages.cpp" // set_movement_moving_averages
#include "set_open_position_prices.cpp"     // set_open_position_prices
#include "set_moving_price_range.cpp"       // set_moving_price_range
#include "set_position_status.cpp"          // set_order_statuses
#include "shift_transmission_gear.cpp"      // shift_transmission_gear
#include <chrono>                           // std::chrono
#include <thread>                           // std::this_thread

void ETrade::StockBot::watch() {
  while (true) {
    fetch_quote();

    log_quote();
    log_simple_moving_average();
    set_moving_price_range(2 * 60 * 60);
    log_moving_price_range();
    log_position();
    set_movement_moving_averages();

    fetch_orders();
    set_position_status();
    open_position();
    set_open_position_prices();

    shift_transmission_gear();
    this->transmission.log();

    close_position();
    log_position_results();
    reset_position();

    std::this_thread::sleep_for(
        std::chrono::milliseconds((int)(POLLING_INTERVAL_SECONDS * 1000)));
  }
}

#endif
