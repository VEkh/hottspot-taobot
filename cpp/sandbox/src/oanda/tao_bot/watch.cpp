#ifndef OANDA__TAO_BOT_watch
#define OANDA__TAO_BOT_watch

/*
 * Oanda::TaoBot
 */
#include "tao_bot.h"

#include "await_market_open.cpp" // await_market_open
#include "fetch_quote.cpp"       // fetch_quote
#include "is_market_open.cpp"    // is_market_open
#include "log_quote.cpp"         // log_quote
#include "should_terminate.cpp"  // should_terminate

void Oanda::TaoBot::watch() {
  while (!is_market_open()) {
    await_market_open();
  }

  while (!should_terminate()) {
    fetch_quote();

    log_quote();

    std::this_thread::sleep_for(std::chrono::milliseconds(
        (int)(this->POLLING_INTERVAL_SECONDS * 1000)));
  }
}

#endif
