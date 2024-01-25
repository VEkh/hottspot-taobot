// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_trend_reversing
#define ALPACA__TAO_BOT_is_trend_reversing

#include "tao_bot.h" // Alpaca::TaoBot
#include <iterator>  // std::advance, std::next

bool Alpaca::TaoBot::is_trend_reversing() {
  const int range_n = 5;
  const int start_index = this->latest_candles.size() - range_n;

  std::list<candle_t>::iterator it = this->latest_candles.begin();
  std::advance(it, start_index);

  trend_t trend = it->trend();

  for (; it != this->latest_candles.end(); it++) {
    if (it->trend() != trend && std::next(it) != this->latest_candles.end()) {
      break;
    }

    if (it->trend() != trend && std::next(it) == this->latest_candles.end()) {
      return true;
    }
  }

  return false;
}

#endif
