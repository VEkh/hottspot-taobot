#ifndef OANDA__TAO_BOT_dynamic_one_sec_variance
#define OANDA__TAO_BOT_dynamic_one_sec_variance

#include "tao_bot.h" // Oanda::TaoBot
#include <algorithm> // std::max

double Oanda::TaoBot::dynamic_one_sec_variance() {
  return std::max(
      this->price_movement.short_term_three_minute_one_second_variance.average,
      this->price_movement.three_minute_one_second_variance.average);
}

#endif
