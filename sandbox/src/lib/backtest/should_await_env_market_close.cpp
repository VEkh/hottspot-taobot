#ifndef BACKTEST_should_await_env_market_close
#define BACKTEST_should_await_env_market_close

#include "backtest.h"             // Alpaca::TaoBotBacktest
#include "has_reached_end.cpp"    // has_reached_end
#include "lib/utils/iterable.cpp" // ::utils::iterable
#include "lib/utils/time.cpp"     // ::utils::time_
#include <string>                 // std::stod, std::string
#include <time.h>                 // localtime

bool Backtest::should_await_env_market_close(
    const double market_close_epoch, const double next_market_open_epoch) {
  if (!this->is_active) {
    return false;
  }

  if (!this->config.clock_sync) {
    return false;
  }

  if (has_reached_end(next_market_open_epoch)) {
    return false;
  }

  const std::list<std::string> market_closed_symbols =
      this->db_market_close.get_symbols_closed_at({
          .api_key_id = this->config.api_key_id,
          .epoch = market_close_epoch,
      });

  return !::utils::iterable::are_equal(market_closed_symbols,
                                       this->env_symbols);
}

#endif
