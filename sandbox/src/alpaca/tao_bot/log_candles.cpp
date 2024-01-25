// TODO: Decide
#ifndef ALPACA__TAO_BOT_log_candles
#define ALPACA__TAO_BOT_log_candles

#include "candles_range.cpp"  // candles_range
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, candle_t, fmt, range_t, trend_t
#include <iostream>           // std::cout, std::endl
#include <iterator>           // std::advance
#include <list>               // std::list
#include <stdio.h>            // printf

void Alpaca::TaoBot::log_candles(const int range_n) {
  const range_t range = candles_range(range_n);

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf(
      "Last %i Candles (%s -> %s)\n", range_n,
      ::utils::time_::date_string(range.opened_at, "%H:%M", "America/Chicago")
          .c_str(),
      ::utils::time_::date_string(range.closed_at, "%H:%M", "America/Chicago")
          .c_str());
  std::cout << fmt.reset;

  const int start_index = this->latest_candles.size() - range_n;
  std::list<candle_t>::iterator it = this->latest_candles.begin();
  std::advance(it, start_index);

  for (; it != this->latest_candles.end(); it++) {
    switch (it->trend()) {
    case trend_t::TREND_CONSOLIDATION: {
      printf("🟡");
      break;
    }
    case trend_t::TREND_DOWN: {
      printf("🔴");
      break;
    }
    case trend_t::TREND_UP: {
      printf("🟢");
      break;
    }
    }
  }

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif
