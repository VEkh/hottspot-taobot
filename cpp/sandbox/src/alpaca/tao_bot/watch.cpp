#ifndef ALPACA__TAO_BOT_watch
#define ALPACA__TAO_BOT_watch

#include "fetch_quote.cpp"         // fetch_quote
#include "log_account_balance.cpp" // log_account_balance
#include "log_quote.cpp"           // log_quote
#include "should_terminate.cpp"    // should_terminate
#include "tao_bot.h"               // Alpaca::TaoBot
#include <unistd.h>                // usleep

void Alpaca::TaoBot::watch() {
  while (!should_terminate()) {
    fetch_quote();

    log_account_balance();
    log_quote();

    usleep(1e6);
  }
}

#endif
