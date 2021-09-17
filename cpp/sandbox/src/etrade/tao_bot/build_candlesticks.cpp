#ifndef ETRADE__TAO_BOT_build_candlesticks
#define ETRADE__TAO_BOT_build_candlesticks

#include "tao_bot.h" // ETrade::TaoBot, candlestick_t, quote_t
#include <algorithm> // std::max, std:min
#include <list>      // std::list
#include <time.h>    // localtime, time_t, tm
#include <vector>    // std::vector

#include <stdlib.h> // getenv, setenv, unsetenv
#include <string>   // std::string
#include <time.h>   // localtime time_t

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

  std::string (*timestamp_to_clock)(time_t) =
      [](time_t timestamp) -> std::string {
    const char *original_tz = getenv("TZ");
    setenv("TZ", "America/New_York", 1);

    tm quote_time = *localtime(&timestamp);

    const std::string out = std::to_string(quote_time.tm_hour) + ":" +
                            std::to_string(quote_time.tm_min);

    if (original_tz) {
      setenv("TZ", original_tz, 1);
    } else {
      unsetenv("TZ");
    }

    return out;
  };

  candlestick_t candlestick = {
      .clock_time = timestamp_to_clock(it->timestamp),
      .close = it->current_price,
      .high = it->current_price,
      .low = it->current_price,
  };

  while (this->candlesticks.size() < max_candles) {
    std::string clock_time = timestamp_to_clock(it->timestamp);

    if (candlestick.clock_time == clock_time) {
      candlestick.high = std::max(candlestick.high, it->current_price);
      candlestick.low = std::min(candlestick.low, it->current_price);

      it++;

      continue;
    }

    candlestick.open = (it - 1)->current_price;

    this->candlesticks.push_front(candlestick);

    candlestick = {
        .clock_time = timestamp_to_clock(it->timestamp),
        .close = it->current_price,
        .high = it->current_price,
        .low = it->current_price,
    };

    it++;
  }
}

#endif
