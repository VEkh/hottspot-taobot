#ifndef ALPACA__TAO_BOT_BACKTEST_should_exec_slow_query
#define ALPACA__TAO_BOT_BACKTEST_should_exec_slow_query

#include "backtest.h"          // Alpaca::TaoBotBacktest
#include "has_reached_end.cpp" // has_reached_end

bool Alpaca::TaoBotBacktest::should_exec_slow_query(
    const double current_epoch) {
  if (has_reached_end(current_epoch)) {
    return true;
  }

  return this->slow_query_countdown % this->SLOW_QUERY_EVERY == 0;
}

#endif
