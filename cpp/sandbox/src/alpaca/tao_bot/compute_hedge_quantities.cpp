#ifndef ALPACA__TAO_BOT_compute_hedge_quantities
#define ALPACA__TAO_BOT_compute_hedge_quantities

#include "hedge_symbol.cpp" // hedge_symbol
#include "tao_bot.h"        // Alpaca::TaoBot
#include <algorithm>        // std::min
#include <math.h>           // floor
#include <utility>          // std::pair

std::pair<double, double> Alpaca::TaoBot::compute_hedge_quantities() {
  const quote_t base_quote = this->quotes.back();
  const quote_t hedge_quote = this->hedge_quotes.back();

  const double base_one_sec_variance =
      this->price_movements[this->symbol]
          .three_minute_one_second_variance.average;

  const double hedge_one_sec_variance =
      this->price_movements[hedge_symbol()]
          .three_minute_one_second_variance.average;

  double base_quantity_ = 1.0;
  double hedge_quantity = base_one_sec_variance / hedge_one_sec_variance;

  if (hedge_one_sec_variance >= base_one_sec_variance ||
      this->HEDGE_PAIRS[this->symbol].action == order_action_t::SELL) {
    hedge_quantity = 1.0;
    base_quantity_ = hedge_one_sec_variance / base_one_sec_variance;
  }

  return {base_quantity_, hedge_quantity};
}

#endif
