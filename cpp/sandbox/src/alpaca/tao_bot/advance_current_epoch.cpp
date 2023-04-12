#ifndef ALPACA__TAO_BOT_advance_current_epoch
#define ALPACA__TAO_BOT_advance_current_epoch

#include "tao_bot.h" // Alpaca::TaoBot
#include <time.h>    // time
#include <unistd.h>  // usleep

void Alpaca::TaoBot::advance_current_epoch() {
  if (!this->backtest.has_reached_now(this->current_epoch)) {
    advance_current_epoch(this->current_epoch + 0.5);
    this->backtest.slow_query_countdown += 1;
  } else {
    usleep(5e5);

    advance_current_epoch(time(nullptr));
  }
}

void Alpaca::TaoBot::advance_current_epoch(const double epoch) {
  this->current_epoch = epoch;
}

#endif
