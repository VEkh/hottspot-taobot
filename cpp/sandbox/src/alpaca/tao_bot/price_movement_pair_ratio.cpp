#ifndef ALPACA__TAO_BOT_price_movement_pair_ratio
#define ALPACA__TAO_BOT_price_movement_pair_ratio

#include "tao_bot.h" // Alpaca::TaoBot, quote_t
#include <math.h>    // abs
#include <string>    // std::string
#include <vector>    // std::vector

Alpaca::TaoBot::price_movement_average_t
Alpaca::TaoBot::price_movement_pair_ratio(std::vector<quote_t> &quotes_a,
                                          std::vector<quote_t> &quotes_b,
                                          const std::string symbol_) {
  const int sample_size = 150;

  if (quotes_a.size() < (sample_size + 1) ||
      quotes_b.size() < (sample_size + 1)) {
    return this->price_movements[symbol_].ratio_from_hedge;
  }

  double total_a = 0;
  double total_b = 0;
  int i = sample_size;
  std::vector<quote_t>::reverse_iterator it_a;
  std::vector<quote_t>::reverse_iterator it_b;

  for (it_a = quotes_a.rbegin(), it_b = quotes_b.rbegin(); i >= 0;
       it_a++, it_b++, i--) {
    total_a += abs(it_a->price - (it_a + 1)->price);
    total_b += abs(it_b->price - (it_b + 1)->price);
  }

  const double average = total_a / total_b;

  if (average > 1.0e6) {
    return this->price_movements[symbol_].ratio_from_hedge;
  }

  return {.average = average, .count = sample_size};
}

#endif
