#ifndef ALPACA__TAO_BOT_volatility
#define ALPACA__TAO_BOT_volatility

#include "tao_bot.h" // Alpaca::TaoBot, order_t
#include <string>    // std::string

double Alpaca::TaoBot::volatility(const order_t *order_ptr) {
  return volatility(order_ptr->symbol);
}

double Alpaca::TaoBot::volatility(const std::string &symbol_) {
  const double one_second_variance =
      this->price_movements[symbol_].three_minute_one_second_variance.average;

  const double short_term_one_second_variance =
      this->price_movements[symbol_]
          .short_term_three_minute_one_second_variance.average;

  return short_term_one_second_variance / one_second_variance;
}

#endif
