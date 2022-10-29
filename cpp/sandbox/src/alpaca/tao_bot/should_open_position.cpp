#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "is_breaking_out.cpp" // is_breaking_out
#include "is_market_open.cpp"  // is_market_open
#include "is_price_moving.cpp" // is_price_moving
#include "tao_bot.h"           // Alpaca::TaoBot, quote_t
#include <ctime>               // std::time
#include <math.h>              // abs
#include <vector>              // std:vector

bool Alpaca::TaoBot::should_open_position() {
  if (!is_market_open()) {
    return false;
  }

  if (this->open_order_ptr) {
    return false;
  }

  if (!this->price_movement.short_term_three_minute_one_second_variance
           .average) {
    return false;
  }

  if (!is_price_moving()) {
    return false;
  }

  if (!is_breaking_out()) {
    return false;
  }

  return true;
}

#endif
