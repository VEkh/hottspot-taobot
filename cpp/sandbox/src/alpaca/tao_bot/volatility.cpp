#ifndef ALPACA__TAO_BOT_volatility
#define ALPACA__TAO_BOT_volatility

#include "tao_bot.h" // Alpaca::TaoBot, order_t
#include <string>    // std::string

double Alpaca::TaoBot::volatility() {
  const double one_second_variance =
      this->price_movement.three_minute_one_second_variance.average;

  const double short_term_one_second_variance =
      this->price_movement.short_term_three_minute_one_second_variance.average;

  return short_term_one_second_variance / one_second_variance;
}

#endif
