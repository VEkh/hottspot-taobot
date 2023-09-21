#ifndef ALPACA__TAO_BOT_watch
#define ALPACA__TAO_BOT_watch

#include "advance_current_epoch.cpp"     // advance_current_epoch
#include "cancel_stale_open_order.cpp"   // cancel_stale_open_order
#include "close_position.cpp"            // close_position
#include "log_account_snapshot.cpp"      // log_account_snapshot
#include "log_end_of_trading_period.cpp" // log_end_of_trading_period
#include "log_five_min_predictions.cpp"  // log_five_min_predictions
#include "log_performance.cpp"           // log_performance
#include "log_position.cpp"              // log_position
#include "log_position_results.cpp"      // log_position_results
#include "log_price_movement.cpp"        // log_price_movement
#include "log_quote.cpp"                 // log_quote
#include "log_timestamps.cpp"            // log_timestamps
#include "open_and_persist_position.cpp" // open_and_persist_position
#include "read_price_movement.cpp"       // price_movement
#include "read_quotes.cpp"               // read_quotes
#include "reset_backtest.cpp"            // reset_backtest
#include "reset_position.cpp"            // reset_position
#include "set_close_order_prices.cpp"    // set_close_order_prices
#include "set_open_order_prices.cpp"     // set_open_order_prices
#include "set_position_status.cpp"       // set_order_statuses
#include "should_terminate.cpp"          // should_terminate
#include "tao_bot.h"                     // Alpaca::TaoBot
#include "update_account_snapshot.cpp"   // update_account_snapshot
#include <iostream>                      // std::cout, std::flush

void Alpaca::TaoBot::watch() {
  while (!should_terminate()) {
    if (this->backtest.should_exec_slow_query(this->current_epoch)) {
      log_timestamps();
    }

    read_quotes();
    read_price_movement();
    update_account_snapshot();

    if (this->backtest.should_exec_slow_query(this->current_epoch)) {
      log_account_snapshot();
      log_quote();
      log_price_movement();
      log_five_min_predictions();
      log_position();
      log_performance();
    }

    set_position_status();
    cancel_stale_open_order();
    open_and_persist_position();
    set_open_order_prices();

    close_position();
    set_close_order_prices();

    log_position_results();
    reset_position();

    if (this->backtest.should_exec_slow_query(this->current_epoch)) {
      std::cout << "\n\n\n\n\n\n\n\n\n\n" << std::flush;
    }

    advance_current_epoch();
  }

  update_account_snapshot(true);
  log_timestamps();
  log_account_snapshot();
  log_end_of_trading_period();

  if (this->backtest.is_active &&
      !this->backtest.has_reached_end(this->current_epoch)) {
    reset_backtest();

    return watch();
  }

  this->pg.disconnect();
}

#endif
