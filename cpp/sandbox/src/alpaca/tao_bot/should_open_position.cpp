#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "is_market_open.cpp" // is_market_open
#include "tao_bot.h"          // Alpaca::TaoBot, quote_t

#include "batch_volatility.cpp" // batch_volatility
#include "lib/utils/time.cpp"   // ::utils::time_

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

  if (batch_volatility() < 1.2) {
    return ::utils::time_::is_before({8, 31}, "America/Chicago");
  }

  return true;
}

#endif
