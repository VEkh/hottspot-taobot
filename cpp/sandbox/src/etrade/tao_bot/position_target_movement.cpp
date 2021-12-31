#ifndef ETRADE__TAO_BOT_position_target_movement
#define ETRADE__TAO_BOT_position_target_movement

#include "tao_bot.h" // ETrade::TaoBot

double ETrade::TaoBot::position_target_movement() {
  return this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta;
}

#endif
