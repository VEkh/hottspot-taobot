#ifndef OANDA__TAO_BOT_position_target_movement
#define OANDA__TAO_BOT_position_target_movement

#include "current_spread.cpp" // current_spread
#include "tao_bot.h"          // Oanda::TaoBot

double Oanda::TaoBot::position_target_movement() {
  return this->MAX_SPREAD_TO_OPEN_RATIO * current_spread();
}

#endif
