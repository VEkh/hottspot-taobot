#ifndef ALPACA__TAO_BOT_BACKTEST_has_reached_now
#define ALPACA__TAO_BOT_BACKTEST_has_reached_now

#include "backtest.h" // Alpaca::TaoBotBacktest
#include "time.h"     // time

bool Alpaca::TaoBotBacktest::has_reached_now(const double current_epoch) {
  if (!this->is_active) {
    return true;
  }

  const long int now = time(nullptr);
  return current_epoch >= now;
}

#endif
