#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "hedge_symbol.cpp" // hedge_symbol
#include "is_hedging.cpp"   // is_hedging
#include "tao_bot.h"        // Alpaca::TaoBot

bool Alpaca::TaoBot::should_open_position(const order_t *order_ptr) {
  if (order_ptr) {
    return false;
  }

  if (!this->price_movements[this->symbol]
           .three_minute_one_second_variance.average) {
    return false;
  }

  if (is_hedging() && !this->price_movements[hedge_symbol()]
                           .three_minute_one_second_variance.average) {
    return false;
  }

  return true;
}

#endif
