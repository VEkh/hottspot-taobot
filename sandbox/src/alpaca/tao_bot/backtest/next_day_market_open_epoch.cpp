#ifndef ALPACA__TAO_BOT_BACKTEST_next_day_market_open_epoch
#define ALPACA__TAO_BOT_BACKTEST_next_day_market_open_epoch

#include "backtest.h"         // Alpaca::TaoBotBacktest
#include "lib/utils/time.cpp" // ::utils::time_
#include <algorithm>          // std::min
#include <string>             // std::string

int Alpaca::TaoBotBacktest::next_day_market_open_epoch(
    const double current_epoch, const int late_start_seconds = 0) {
  const double tomorrow_epoch = current_epoch + (24 * 60 * 60);

  const std::string tomorrow_date_string =
      ::utils::time_::date_string(tomorrow_epoch, "%F", "America/Chicago");

  const long int next_open_epoch =
      this->db_utils.timestamp_to_epoch(tomorrow_date_string + " 08:30:00",
                                        "America/Chicago") +
      late_start_seconds;

  const long int now = time(nullptr);

  return std::min(now, next_open_epoch);
}

#endif
