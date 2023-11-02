#ifndef ALPACA__TAO_BOT_advance_current_epoch
#define ALPACA__TAO_BOT_advance_current_epoch

#include "tao_bot.h" // Alpaca::TaoBot
#include <time.h>    // time
#include <unistd.h>  // usleep

void Alpaca::TaoBot::advance_current_epoch() {
  if (this->backtest.is_active) {
    const double clock_tick_seconds = 1.0;

    advance_current_epoch(this->current_epoch + clock_tick_seconds);
    this->backtest.slow_query_countdown += 1;
    return;
  }

  usleep(5e5);

  advance_current_epoch(time(nullptr));
}

void Alpaca::TaoBot::advance_current_epoch(const double epoch) {
  if (this->backtest.should_await_epoch_advance(this->current_epoch, epoch)) {
    return advance_current_epoch(epoch);
  }

  this->current_epoch = epoch;
}

#endif
