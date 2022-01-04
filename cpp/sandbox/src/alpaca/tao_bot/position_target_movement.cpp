#ifndef ALPACA__TAO_BOT_position_target_movement
#define ALPACA__TAO_BOT_position_target_movement

#include "tao_bot.h" // Alpaca::TaoBot

double Alpaca::TaoBot::position_target_movement() {
  return this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta;
}

#endif
