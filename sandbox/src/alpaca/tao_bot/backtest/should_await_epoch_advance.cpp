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

  if (has_reached_end(new_epoch)) {
    return false;
  }

  const double current_begin_day_epoch =
      ::utils::time_::beginning_of_day_to_epoch(current_epoch);

  const double new_begin_day_epoch =
      ::utils::time_::beginning_of_day_to_epoch(new_epoch);

  const bool is_new_day = new_begin_day_epoch != current_begin_day_epoch;

  publish_clock(new_epoch);

  if (!is_new_day) {
    return false;
  }

  const std::string sibling_epoch_string = subscribe_clock();

  if (sibling_epoch_string.empty()) {
    return true;
  }

  const double sibling_begin_day_epoch =
      ::utils::time_::beginning_of_day_to_epoch(
          std::stod(sibling_epoch_string));

  if (sibling_begin_day_epoch < new_begin_day_epoch) {
    return true;
  }

  return false;
}

#endif
