#ifndef ALPACA__TAO_BOT_position_target_movement
#define ALPACA__TAO_BOT_position_target_movement

#include "min_target_tick_movement.cpp" // min_target_tick_movement
#include "tao_bot.h"                    // Alpaca::TaoBot

double Alpaca::TaoBot::position_target_movement() {
  return min_target_tick_movement() *
         this->price_movements.three_minute_one_second_variance.average;
}

#endif
