#ifndef ALPACA__TAO_BOT_BACKTEST_should_exec_slow_query
#define ALPACA__TAO_BOT_BACKTEST_should_exec_slow_query

#include "backtest.h" // Alpaca::TaoBotBacktest

bool Alpaca::TaoBotBacktest::should_exec_slow_query() {
  if (!this->is_active) {
    return true;
  }

  return this->slow_query_countdown % this->SLOW_QUERY_EVERY == 0;
}

#endif
