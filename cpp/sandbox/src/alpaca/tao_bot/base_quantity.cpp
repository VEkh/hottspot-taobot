#ifndef ALPACA__TAO_BOT_base_quantity
#define ALPACA__TAO_BOT_base_quantity

#include "position_target_movement.cpp" // position_target_movement
#include "tao_bot.h"                    // Alpaca::TaoBot

double Alpaca::TaoBot::base_quantity() {
  const double target_profit =
      this->account_balance.balance * this->POSITION_TARGET_PROFIT_RATIO;

  return target_profit / position_target_movement();
}

#endif
