#ifndef OANDA__TAO_BOT_base_quantity
#define OANDA__TAO_BOT_base_quantity

#include "tao_bot.h" // Oanda::TaoBot
#include <math.h>    // ceil

int Oanda::TaoBot::base_quantity() {
  const double target_profit = this->account_balance.balance * 2e-5;

  const int base_quantity_ =
      ceil(target_profit /
           (this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta));

  return base_quantity_;
}

#endif
