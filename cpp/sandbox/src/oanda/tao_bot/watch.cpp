#ifndef OANDA__TAO_BOT_watch
#define OANDA__TAO_BOT_watch

#include "await_market_open.cpp"  // await_market_open
#include "build_candlesticks.cpp" // build_candlesticks
#include "fetch_quote.cpp"        // fetch_quote
#include "is_market_open.cpp"     // is_market_open
#include "log_candlesticks.cpp"   // log_candlesticks
#include "log_quote.cpp"          // log_quote
#include "should_terminate.cpp"   // should_terminate
#include "tao_bot.h"              // Oanda::TaoBot

void Oanda::TaoBot::watch() {
  while (!is_market_open()) {
    await_market_open();
  }

  while (!should_terminate()) {
    fetch_quote();
    build_candlesticks();

    log_quote();
    log_candlesticks();

    std::this_thread::sleep_for(std::chrono::milliseconds(
        (int)(this->POLLING_INTERVAL_SECONDS * 1000)));
  }
}

#endif
