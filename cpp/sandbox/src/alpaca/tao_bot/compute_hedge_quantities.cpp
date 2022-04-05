#ifndef ALPACA__TAO_BOT_compute_hedge_quantities
#define ALPACA__TAO_BOT_compute_hedge_quantities

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::min
#include <math.h>    // floor
#include <utility>   // std::pair

std::pair<double, double> Alpaca::TaoBot::compute_hedge_quantities() {
  const quote_t base_quote = this->quotes.back();
  const quote_t hedge_quote = this->hedge_quotes.back();
  double base_quantity_ = 1.0;
  double hedge_quantity = base_quote.ask / hedge_quote.ask;

  if (hedge_quote.ask >= base_quote.ask ||
      this->HEDGE_PAIRS[this->symbol].action == order_action_t::SELL) {
    hedge_quantity = 1.0;
    base_quantity_ = hedge_quote.ask / base_quote.ask;
  }

  return {base_quantity_, hedge_quantity};
}

#endif
