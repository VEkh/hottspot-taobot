#ifndef ETRADE__TAO_BOT_watch
#define ETRADE__TAO_BOT_watch

#include "await_market_open.cpp"            // await_market_open
#include "awaited_loss_leader.cpp"          // awaited_loss_leader
#include "build_candlesticks.cpp"           // build_candlesticks
#include "cancel_stale_open_order.cpp"      // cancel_stale_open_order
#include "close_position.cpp"               // close_position
#include "fetch_quote.cpp"                  // fetch_quote
#include "is_market_open.cpp"               // is_market_open
#include "lib/utils/time.cpp"               // utils::time_
#include "log_account_balance.cpp"          // log_account_balance
#include "log_average_tick_price_delta.cpp" // log_average_tick_price_delta
#include "log_candlesticks.cpp"             // log_candlesticks
#include "log_end_of_trading_period.cpp"    // log_end_of_trading_period
#include "log_performance.cpp"              // log_performance
#include "log_position.cpp"                 // log_position
#include "log_position_results.cpp"         // log_position_results
#include "log_quote.cpp"                    // log_quote
#include "open_position.cpp"                // open_position
#include "reset_position.cpp"               // reset_position
#include "set_and_log_buy_sell_ratios.cpp"  // set_and_log_buy_sell_ratios
#include "set_average_tick_price_delta.cpp" // set_average_tick_price_delta
#include "set_close_position_prices.cpp"    // set_open_position_prices
#include "set_open_position_prices.cpp"     // set_open_position_prices
#include "set_position_status.cpp"          // set_order_statuses
#include "should_terminate.cpp"             // should_terminate
#include "tao_bot.h"                        // ETrade::TaoBot
#include <unistd.h>                         // usleep

void ETrade::TaoBot::watch() {
  while (!is_market_open()) {
    await_market_open();
  }

  while (!should_terminate()) {
    fetch_quote();
    build_candlesticks();
    set_average_tick_price_delta();

    if (awaited_loss_leader()) {
      continue;
    }

    log_account_balance();
    log_quote();
    log_candlesticks();
    set_and_log_buy_sell_ratios();
    log_average_tick_price_delta();
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

    usleep(1e6);
  }

  log_end_of_trading_period();
}

#endif
