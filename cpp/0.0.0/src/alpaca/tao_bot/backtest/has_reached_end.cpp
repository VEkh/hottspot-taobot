#ifndef ALPACA__TAO_BOT_BACKTEST_has_reached_end
#define ALPACA__TAO_BOT_BACKTEST_has_reached_end

#include "backtest.h" // Alpaca::TaoBotBacktest
#include <time.h>     // time

bool Alpaca::TaoBotBacktest::has_reached_end(const double current_epoch) {
  return current_epoch >= this->config.end_epoch;
}

#endif
