#ifndef ALPACA__TAO_BOT_BACKTEST_should_await_epoch_advance
#define ALPACA__TAO_BOT_BACKTEST_should_await_epoch_advance

#include "backtest.h"          // Alpaca::TaoBotBacktest
#include "publish_clock.cpp"   // publish_clock
#include "subscribe_clock.cpp" // subscribe_clock
#include <string>              // std::stod, std::string
#include <time.h>              // localtime

bool Alpaca::TaoBotBacktest::should_await_epoch_advance(
    const long int current_epoch, const long int new_epoch) {
  if (!this->is_active) {
    return false;
  }

  if (!this->config.clock_sync) {
    return false;
  }

  tm current_tm = *localtime(&current_epoch);
  tm new_epoch_tm = *localtime(&new_epoch);

  const bool is_new_day = new_epoch_tm.tm_mday != current_tm.tm_mday;

  publish_clock(new_epoch, is_new_day);

  if (!is_new_day) {
    return false;
  }

  const std::string sibling_epoch_string = subscribe_clock(true);

  if (sibling_epoch_string.empty()) {
    return true;
  }

  const long int sibling_epoch = std::stod(sibling_epoch_string);

  tm sibling_epoch_tm = *localtime(&sibling_epoch);

  if (sibling_epoch_tm.tm_mday < new_epoch_tm.tm_mday) {
    return true;
  }

  return false;
}

#endif
