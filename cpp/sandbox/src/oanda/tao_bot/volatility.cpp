#ifndef OANDA__TAO_BOT_volatility
#define OANDA__TAO_BOT_volatility

#include "tao_bot.h" // Oanda::TaoBot, order_t
#include <string>    // std::string

double Oanda::TaoBot::volatility() {
  const double one_second_variance =
      this->price_movement.three_minute_one_second_variance.average;

  const double short_term_one_second_variance =
      this->price_movement.short_term_three_minute_one_second_variance.average;

  return short_term_one_second_variance / one_second_variance;
}

#endif
