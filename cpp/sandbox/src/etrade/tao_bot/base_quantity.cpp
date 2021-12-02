#ifndef ETRADE__TAO_BOT_base_quantity
#define ETRADE__TAO_BOT_base_quantity

#include "tao_bot.h" // ETrade::TaoBot
#include <math.h>    // ceil

int ETrade::TaoBot::base_quantity() {
  const double target_profit =
      this->account_balance.balance * this->POSITION_TARGET_PROFIT_RATIO;

  const int base_quantity_ =
      ceil(target_profit /
           (this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta));

  return this->quantity_mulitiplier * base_quantity_;
}

#endif
