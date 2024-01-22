// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_consolidating
#define ALPACA__TAO_BOT_is_consolidating

#include "candles_range.cpp" // candles_range
#include "tao_bot.h"         // Alpaca::TaoBot, range_t
#include <iterator>          // std::advance
#include <list>              // std::list
#include <math.h>            // abs

bool Alpaca::TaoBot::is_consolidating() {
  const int range_n = this->api_client.config.consolidation_duration_mintues;

  range_t range = candles_range(range_n);

  const double mean = 0.5 * (range.high + range.low);
  double mean_contain_count = 0;
  int count = 0;

  std::list<candle_t>::iterator it = this->latest_candles.begin();

  const int start_index = this->latest_candles.size() - range_n;
  std::advance(it, start_index);

  for (; it != this->latest_candles.end() && count < range_n; it++, count++) {
    if (mean <= it->high && mean >= it->low) {
      mean_contain_count += 1;
    }
  }

  const double mean_contain_ratio = mean_contain_count / range_n;

  if (mean_contain_ratio < 0.8) {
    return false;
  }

  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const int half_range_n = range_n / 2;

  const int first_range_start_index = this->latest_candles.size() - range_n;
  const int second_range_start_index =
      this->latest_candles.size() - range_n + half_range_n;

  range_t first_half_range =
      candles_range(first_range_start_index, half_range_n);

  range_t second_half_range =
      candles_range(second_range_start_index, half_range_n);

  const double high_delta = abs(first_half_range.high - second_half_range.high);
  const double low_delta = abs(first_half_range.low - second_half_range.low);

  return high_delta <= 10 * static_one_sec_variance &&
         low_delta <= 10 * static_one_sec_variance;
}

#endif
