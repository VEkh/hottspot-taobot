#ifndef OANDA__TAO_BOT_watch
#define OANDA__TAO_BOT_watch

#include "advance_current_epoch.cpp"     // advance_current_epoch
#include "clear_stale_open_order.cpp"    // clear_stale_open_order
#include "close_position.cpp"            // close_position
#include "is_market_open.cpp"            // is_market_open
#include "log_account_snapshot.cpp"      // log_account_snapshot
#include "log_end_of_trading_period.cpp" // log_end_of_trading_period
#include "log_performance.cpp"           // log_performance
#include "log_position.cpp"              // log_position
#include "log_position_results.cpp"      // log_position_results
#include "log_price_movement.cpp"        // log_price_movement
#include "log_quote.cpp"                 // log_quote
#include "log_timestamps.cpp"            // log_timestamps
#include "open_and_persist_position.cpp" // open_and_persist_position
#include "read_price_movement.cpp"       // price_movement
#include "read_quotes.cpp"               // read_quotes
#include "reset_position.cpp"            // reset_position
#include "set_close_order_prices.cpp"    // set_close_order_prices
#include "set_open_order_prices.cpp"     // set_open_order_prices
#include "set_position_status.cpp"       // set_order_statuses
#include "should_terminate.cpp"          // should_terminate
#include "tao_bot.h"                     // Oanda::TaoBot
#include "update_account_snapshot.cpp"   // update_account_snapshot
#include <iostream>                      // std::cout, std::flush
#include <unistd.h>                      // usleep

void Oanda::TaoBot::watch() {
  while (!should_terminate()) {
    log_timestamps();

    read_quotes();
    read_price_movement();
    update_account_snapshot();

    log_account_snapshot();
    log_quote();
    log_price_movement();
    log_position();
    log_performance();

    set_position_status();
    clear_stale_open_order();
    open_and_persist_position();
    set_open_order_prices();

    close_position();
    set_close_order_prices();

    log_position_results();
    reset_position();

    std::cout << std::flush;

    advance_current_epoch();
  }

  log_end_of_trading_period();

  this->pg.disconnect();
}

#endif
