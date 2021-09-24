#ifndef ETRADE__TAO_BOT_base_quantity
#define ETRADE__TAO_BOT_base_quantity

#include "tao_bot.h" // ETrade::TaoBot
#include <math.h>    // ceil

int ETrade::TaoBot::base_quantity() {
  const double target_profit = 0.5;
  const double variance_multiplier = 20;

  const int base_quantity_ = ceil(
      target_profit / (variance_multiplier * this->average_tick_price_delta));

  return this->quantity_mulitiplier * base_quantity_;
}

#endif
