#ifndef ALPACA__TAO_BOT_BACKTEST_subscribe_clock
#define ALPACA__TAO_BOT_BACKTEST_subscribe_clock

#include "backtest.h"            // Alpaca::TaoBotBacktest
#include "pub_sub_clock_key.cpp" // pub_sub_clock_key
#include <string>                // std::string

std::string Alpaca::TaoBotBacktest::subscribe_clock(const bool debug = false) {
  return this->pg.await_notification({
      .channel = pub_sub_clock_key(),
      .debug = debug,
      .timeout_microseconds = (int)1e6,
  });
}

#endif
