// TODO: Decide
#ifndef ALPACA__TAO_BOT_candles_range
#define ALPACA__TAO_BOT_candles_range

#include "tao_bot.h" // Alpaca::TaoBot
#include <iterator>  // std::advance, std::next
#include <list>      // std::list
#include <valarray>  // std::valarray

Alpaca::TaoBot::range_t Alpaca::TaoBot::candles_range(const int range_n) {
  const int start_index = this->latest_candles.size() - range_n;

  return candles_range(start_index, range_n);
}

Alpaca::TaoBot::range_t Alpaca::TaoBot::candles_range(const int start_index,
                                                      const int range_n) {
  range_t range;

  const int count = range_n ? range_n : this->latest_candles.size();
  int counter = 0;
  std::list<candle_t>::iterator it = this->latest_candles.begin();

  std::advance(it, start_index);

  range.opened_at = it->opened_at;

  for (; it != this->latest_candles.end() && counter < count; it++, counter++) {
    // TODO: Decide
    const std::valarray<double> highs = {range.high, it->close, it->open};
    const std::valarray<double> lows = {range.low, it->close, it->open};

    range.high = highs.max();
    range.low = lows.min();

    // TODO: Decide
    // range.high = std::max(range.high, it->high);
    // range.low = std::min(range.low, it->low);

    range.closed_at = it->closed_at;
  }

  return range;
}

#endif
