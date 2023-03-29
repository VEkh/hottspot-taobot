#ifndef ALPACA__TAO_BOT_dynamic_one_sec_variance
#define ALPACA__TAO_BOT_dynamic_one_sec_variance

// NOTE: Deprecated

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max

double Alpaca::TaoBot::dynamic_one_sec_variance() {
  return std::max(
      this->price_movement.short_term_three_minute_one_second_variance.average,
      this->price_movement.three_minute_one_second_variance.average);
}

#endif
