#ifndef OANDA__TAO_BOT_watch
#define OANDA__TAO_BOT_watch

#include "await_market_open.cpp"            // await_market_open
#include "build_candlesticks.cpp"           // build_candlesticks
#include "cancel_stale_open_order.cpp"      // cancel_stale_open_order
#include "fetch_quote.cpp"                  // fetch_quote
#include "is_market_open.cpp"               // is_market_open
#include "log_account_balance.cpp"          // log_account_balance
#include "log_average_tick_price_delta.cpp" // log_average_tick_price_delta
#include "log_candlesticks.cpp"             // log_candlesticks
#include "log_performance.cpp"              // log_performance
#include "log_position.cpp"                 // log_position
#include "log_quote.cpp"                    // log_quote
#include "set_and_log_buy_sell_ratios.cpp"  // set_and_log_buy_sell_ratios
#include "set_average_tick_price_delta.cpp" // set_average_tick_price_delta
#include "set_position_status.cpp"          // set_order_statuses
#include "should_terminate.cpp"             // should_terminate
#include "tao_bot.h"                        // Oanda::TaoBot

void Oanda::TaoBot::watch() {
  while (!is_market_open()) {
    await_market_open();
  }

  while (!should_terminate()) {
    fetch_quote();
    build_candlesticks();
    set_average_tick_price_delta();

    log_account_balance();
    log_quote();
    log_candlesticks();
    set_and_log_buy_sell_ratios();
    log_average_tick_price_delta();
    log_position();
    log_performance();

    cancel_stale_open_order();
    set_position_status();

    std::this_thread::sleep_for(std::chrono::milliseconds(
        (int)(this->POLLING_INTERVAL_SECONDS * 1000)));
  }
}

#endif
