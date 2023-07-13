#ifndef ALPACA__TAO_BOT_BACKTEST_next_day_market_open_epoch
#define ALPACA__TAO_BOT_BACKTEST_next_day_market_open_epoch

#include "backtest.h"         // Alpaca::TaoBotBacktest
#include "lib/utils/time.cpp" // ::utils::time_
#include <algorithm>          // std::min
#include <time.h>             // localtime, mktime

int Alpaca::TaoBotBacktest::next_day_market_open_epoch(
    const double current_epoch) {
  const double today_start_epoch =
      ::utils::time_::beginning_of_day_to_epoch(current_epoch);

  const long int tomorrow_start = today_start_epoch + (24 * 60 * 60);

  tm market_open = *localtime(&tomorrow_start);
  market_open.tm_hour = 13;
  market_open.tm_min = 30;
  market_open.tm_sec = 0;

  const long int next_open_epoch = mktime(&market_open);
  const long int now = time(nullptr);

  return std::min(now, next_open_epoch);
}

#endif
