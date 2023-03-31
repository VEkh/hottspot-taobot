#ifndef ETRADE__TAO_BOT_base_quantity
#define ETRADE__TAO_BOT_base_quantity

#include "position_target_movement.cpp" // position_target_movement
#include "tao_bot.h"                    // ETrade::TaoBot
#include <math.h>                       // ceil

int ETrade::TaoBot::base_quantity() {
  const double target_profit =
      this->account_snapshot.balance * this->POSITION_TARGET_PROFIT_RATIO;

  const int base_quantity_ = ceil(target_profit / position_target_movement());

  return this->quantity_mulitiplier * base_quantity_;
}

#endif
