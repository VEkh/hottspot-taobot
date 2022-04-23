#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "converted_signaler_price.cpp" // converted_signaler_price
#include "current_price.cpp"            // current_price
#include "hedge_symbol.cpp"             // hedge_symbol
#include "tao_bot.h"                    // Alpaca::TaoBot
#include <math.h>                       // abs

bool Alpaca::TaoBot::should_open_position(const order_t *order_ptr) {
  if (order_ptr) {
    return false;
  }

  if (this->signal.signaler.empty()) {
    return false;
  }

  const double signaled_price = current_price(this->signal.signaled);
  const double converted_signaler_price_ = converted_signaler_price();

  const double price_delta_ratio =
      abs(converted_signaler_price_ - signaled_price) / signaled_price;

  return price_delta_ratio >= 0.001;
}

#endif
