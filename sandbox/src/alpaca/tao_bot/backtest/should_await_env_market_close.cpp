#ifndef ALPACA__TAO_BOT_BACKTEST_should_await_env_market_close
#define ALPACA__TAO_BOT_BACKTEST_should_await_env_market_close

#include "backtest.h"             // Alpaca::TaoBotBacktest
#include "has_reached_end.cpp"    // has_reached_end
#include "lib/utils/iterable.cpp" // ::utils::iterable
#include "lib/utils/time.cpp"     // ::utils::time_
#include <string>                 // std::stod, std::string
#include <time.h>                 // localtime

bool Alpaca::TaoBotBacktest::should_await_env_market_close(
    const double current_epoch, const double next_market_open_epoch) {
  if (!this->is_active) {
    return false;
  }

  if (!this->config.clock_sync) {
    return false;
  }

  if (has_reached_end(next_market_open_epoch)) {
    return false;
  }

  const double current_begin_day_epoch =
      ::utils::time_::beginning_of_day_to_epoch(current_epoch);

  const double new_begin_day_epoch =
      ::utils::time_::beginning_of_day_to_epoch(next_market_open_epoch);

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
                                       this->env_symbols);
}

#endif
