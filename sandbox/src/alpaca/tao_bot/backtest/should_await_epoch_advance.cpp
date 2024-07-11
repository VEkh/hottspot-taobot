#ifndef ALPACA__TAO_BOT_BACKTEST_should_await_epoch_advance
#define ALPACA__TAO_BOT_BACKTEST_should_await_epoch_advance

#include "backtest.h"             // Alpaca::TaoBotBacktest
#include "has_reached_end.cpp"    // has_reached_end
#include "lib/utils/iterable.cpp" // ::utils::iterable
#include "lib/utils/time.cpp"     // ::utils::time_
#include <string>                 // std::stod, std::string
#include <time.h>                 // localtime

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

  if (!is_new_day) {
    return false;
  }

  const std::list<std::string> market_closed_symbols =
      this->db_market_close.get_symbols_closed_at({
          .api_key_id = this->config.api_key_id,
          .epoch = ::utils::time_::beginning_of_day_to_epoch(current_epoch),
      });

  return !::utils::iterable::are_equal(market_closed_symbols,
                                       this->tradeable_symbols);
}

#endif
