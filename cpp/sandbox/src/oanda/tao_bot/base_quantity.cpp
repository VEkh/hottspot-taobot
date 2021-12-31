#ifndef OANDA__TAO_BOT_base_quantity
#define OANDA__TAO_BOT_base_quantity

#include "current_spread.cpp"           // current_spread
#include "position_target_movement.cpp" // position_target_movement
#include "tao_bot.h"                    // Oanda::TaoBot
#include <math.h>                       // ceil

int Oanda::TaoBot::base_quantity() {
  const double target_profit = current_spread();
  const int base_quantity_ = ceil(target_profit / position_target_movement());

  return base_quantity_;
}

#endif
