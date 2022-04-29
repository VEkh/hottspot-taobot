#ifndef ALPACA__TAO_BOT_volatility
#define ALPACA__TAO_BOT_volatility

#include "tao_bot.h" // Alpaca::TaoBot, order_t

double Alpaca::TaoBot::volatility(const order_t *order_ptr) {
  const std::string symbol_ = order_ptr->symbol;

  const double one_second_variance =
      this->price_movements[symbol_].three_minute_one_second_variance.average;

  const double short_term_one_second_variance =
      this->price_movements[symbol_]
          .short_term_three_minute_one_second_variance.average;

  return short_term_one_second_variance / one_second_variance;
}

#endif
