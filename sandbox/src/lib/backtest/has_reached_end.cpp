#ifndef BACKTEST_has_reached_end
#define BACKTEST_has_reached_end

#include "backtest.h" // Backtest

bool Backtest::has_reached_end(const double current_epoch) {
  return current_epoch >= this->config.end_epoch;
}

#endif
