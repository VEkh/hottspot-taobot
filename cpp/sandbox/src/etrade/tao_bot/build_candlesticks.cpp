#ifndef ETRADE__TAO_BOT_build_candlesticks
#define ETRADE__TAO_BOT_build_candlesticks

#include "tao_bot.h" // ETrade::TaoBot, candlestick_t, quote_t
#include <algorithm> // std::max, std:min
#include <list>      // std::list
#include <time.h>    // localtime, time_t, tm
#include <vector>    // std::vector

void ETrade::TaoBot::build_candlesticks() {
  const int period = 60;
  const int max_candles = 4;

  if (this->quotes.empty()) {
    return;
  }

  if ((this->quotes.back().timestamp - this->quotes.front().timestamp) <
      max_candles * period) {
    return;
  }

  this->candlesticks.clear();

  std::vector<quote_t>::reverse_iterator it = this->quotes.rbegin();

  candlestick_t candlestick = {
      .clock_time = ::utils::time_::timestamp_to_clock(it->timestamp),
      .close = it->price,
      .high = it->price,
      .low = it->price,
  };

  while (this->candlesticks.size() < max_candles) {
    std::string clock_time = ::utils::time_::timestamp_to_clock(it->timestamp);

    if (candlestick.clock_time == clock_time) {
      candlestick.high = std::max(candlestick.high, it->price);
      candlestick.low = std::min(candlestick.low, it->price);

      it++;

      continue;
    }

    candlestick.open = (it - 1)->price;

    this->candlesticks.push_front(candlestick);

    candlestick = {
        .clock_time = ::utils::time_::timestamp_to_clock(it->timestamp),
        .close = it->price,
        .high = it->price,
        .low = it->price,
    };

    it++;
  }
}

#endif
