#ifndef ALPACA__TAO_BOT_base_quantity
#define ALPACA__TAO_BOT_base_quantity

#include "position_target_movement.cpp" // position_target_movement
#include "tao_bot.h"                    // Alpaca::TaoBot
#include <math.h>                       // ceil

double Alpaca::TaoBot::base_quantity() {
  const double target_profit = this->account_balance.balance *
                               this->account_balance.margin_multiplier *
                               this->POSITION_TARGET_PROFIT_RATIO;

  const double quantity_ = target_profit / position_target_movement();

  return this->is_long_position ? quantity_ : ceil(quantity_);
}

#endif
