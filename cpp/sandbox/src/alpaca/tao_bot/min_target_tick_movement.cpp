#ifndef ALPACA__TAO_BOT_min_target_tick_movement
#define ALPACA__TAO_BOT_min_target_tick_movement

#include "is_hedging.cpp" // is_hedging
#include "tao_bot.h"      // Alpaca::TaoBot

double Alpaca::TaoBot::min_target_tick_movement() {
  return is_hedging() ? 10 : 20;
}

#endif
