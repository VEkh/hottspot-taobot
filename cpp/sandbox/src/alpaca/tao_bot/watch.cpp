#ifndef ALPACA__TAO_BOT_watch
#define ALPACA__TAO_BOT_watch

#include "await_market_open.cpp"          // await_market_open
#include "await_next_poll.cpp"            // await_next_poll
#include "cancel_stale_open_orders.cpp"   // cancel_stale_open_orders
#include "close_positions.cpp"            // close_positions
#include "fetch_quotes.cpp"               // fetch_quotes
#include "is_market_open.cpp"             // is_market_open
#include "log_account_balance.cpp"        // log_account_balance
#include "log_end_of_trading_period.cpp"  // log_end_of_trading_period
#include "log_performance.cpp"            // log_performance
#include "log_position_results.cpp"       // log_position_results
#include "log_positions.cpp"              // log_positions
#include "log_price_movements.cpp"        // log_price_movements
#include "log_quotes.cpp"                 // log_quotes
#include "log_signals.cpp"                // log_signals
#include "log_timestamps.cpp"             // log_timestamps
#include "open_positions.cpp"             // open_positions
#include "reset_position.cpp"             // reset_position
#include "set_cached_account_balance.cpp" // set_cached_account_balance
#include "set_close_position_prices.cpp"  // set_open_position_prices
#include "set_loss_started_at.cpp"        // set_loss_started_at
#include "set_open_position_prices.cpp"   // set_open_position_prices
#include "set_position_status.cpp"        // set_order_statuses
#include "set_price_movements.cpp"        // set_price_movements
#include "set_profit_started_at.cpp"      // set_profit_started_at
#include "should_terminate.cpp"           // should_terminate
#include "tao_bot.h"                      // Alpaca::TaoBot
#include <iostream>                       // std::cout, std::flush
#include <unistd.h>                       // usleep

void Alpaca::TaoBot::watch() {
  while (!is_market_open()) {
    log_timestamps();
    await_market_open();
  }

  while (!should_terminate()) {
    log_timestamps();
    fetch_quotes();
    set_price_movements();
    set_cached_account_balance();

    log_account_balance();
    log_quotes();
    log_price_movements();
    log_positions();
    log_performance();

    set_position_status();

    cancel_stale_open_orders();
    open_positions();
    set_open_position_prices();
    set_loss_started_at();
    set_profit_started_at();

    close_positions();
    set_close_position_prices();

    log_position_results();
    reset_position();

    std::cout << std::flush;

    await_next_poll();
  }

  log_end_of_trading_period();
}

#endif
