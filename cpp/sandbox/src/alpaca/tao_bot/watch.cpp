#ifndef ALPACA__TAO_BOT_watch
#define ALPACA__TAO_BOT_watch

#include "build_candlesticks.cpp"           // build_candlesticks
#include "cancel_stale_open_order.cpp"      // cancel_stale_open_order
#include "fetch_quote.cpp"                  // fetch_quote
#include "log_account_balance.cpp"          // log_account_balance
#include "log_average_tick_price_delta.cpp" // log_average_tick_price_delta
#include "log_candlesticks.cpp"             // log_candlesticks
#include "log_performance.cpp"              // log_performance
#include "log_position.cpp"                 // log_position
#include "log_quote.cpp"                    // log_quote
#include "open_position.cpp"                // open_position
#include "set_average_tick_price_delta.cpp" // set_average_tick_price_delta
#include "set_position_status.cpp"          // set_order_statuses
#include "should_terminate.cpp"             // should_terminate
#include "tao_bot.h"                        // Alpaca::TaoBot
#include <unistd.h>                         // usleep

void Alpaca::TaoBot::watch() {
  while (!should_terminate()) {
    fetch_quote();
    build_candlesticks();
    set_average_tick_price_delta();

    log_account_balance();
    log_quote();
    log_candlesticks();
    log_average_tick_price_delta();
    log_position();
    log_performance();

    set_position_status();

    cancel_stale_open_order();
    open_position();

    usleep(1e6);
  }
}

#endif
