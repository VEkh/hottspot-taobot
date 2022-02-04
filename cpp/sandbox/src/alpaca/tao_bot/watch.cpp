#ifndef ALPACA__TAO_BOT_watch
#define ALPACA__TAO_BOT_watch

#include "await_market_open.cpp"         // await_market_open
#include "awaited_loss_leader.cpp"       // awaited_loss_leader
#include "build_candlesticks.cpp"        // build_candlesticks
#include "cancel_stale_open_order.cpp"   // cancel_stale_open_order
#include "close_position.cpp"            // close_position
#include "fetch_quote.cpp"               // fetch_quote
#include "is_market_open.cpp"            // is_market_open
#include "log_account_balance.cpp"       // log_account_balance
#include "log_candlesticks.cpp"          // log_candlesticks
#include "log_end_of_trading_period.cpp" // log_end_of_trading_period
#include "log_performance.cpp"           // log_performance
#include "log_position.cpp"              // log_position
#include "log_position_results.cpp"      // log_position_results
#include "log_price_movement.cpp"        // log_price_movement
#include "log_quote.cpp"                 // log_quote
#include "log_timestamps.cpp"            // log_timestamps
#include "open_position.cpp"             // open_position
#include "reset_position.cpp"            // reset_position
#include "set_close_position_prices.cpp" // set_open_position_prices
#include "set_open_position_prices.cpp"  // set_open_position_prices
#include "set_position_status.cpp"       // set_order_statuses
#include "set_price_movement.cpp"        // set_price_movement
#include "should_terminate.cpp"          // should_terminate
#include "tao_bot.h"                     // Alpaca::TaoBot
#include <iostream>                      // std::cout, std::flush
#include <unistd.h>                      // usleep

void Alpaca::TaoBot::watch() {
  while (!is_market_open()) {
    log_timestamps();
    await_market_open();
  }

  while (!should_terminate()) {
    log_timestamps();
    fetch_quote();
    build_candlesticks();
    set_price_movement();

    if (awaited_loss_leader()) {
      continue;
    }

    log_account_balance();
    log_quote();
    log_candlesticks();
    log_price_movement();
    log_position();
    log_performance();

    set_position_status();

    cancel_stale_open_order();
    open_position();
    set_open_position_prices();

    close_position();
    set_close_position_prices();

    log_position_results();
    reset_position();

    std::cout << std::flush;

    usleep(1e6);
  }

  log_end_of_trading_period();
}

#endif
