#ifndef OANDA__TAO_BOT_advance_current_epoch
#define OANDA__TAO_BOT_advance_current_epoch

#include "tao_bot.h" // Oanda::TaoBot
#include <time.h>    // time
#include <unistd.h>  // usleep

void Oanda::TaoBot::advance_current_epoch() {
  if (this->backtest.is_active) {
    advance_current_epoch(this->current_quote.timestamp);

    this->backtest.slow_query_countdown += 1;
    return;
  }

  usleep(5e5);

  advance_current_epoch(time(nullptr));
}

void Oanda::TaoBot::advance_current_epoch(const double epoch) {
  this->current_epoch = epoch;
}

#endif
