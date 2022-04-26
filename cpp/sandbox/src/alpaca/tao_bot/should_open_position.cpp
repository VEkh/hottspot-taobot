#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "converted_signaler_price.cpp" // converted_signaler_price
#include "current_price.cpp"            // current_price
#include "hedge_symbol.cpp"             // hedge_symbol
#include "tao_bot.h"                    // Alpaca::TaoBot
#include <ctime>                        // std::time
#include <math.h>                       // abs

bool Alpaca::TaoBot::should_open_position(const order_t *order_ptr) {
  if (order_ptr) {
    return false;
  }

  if (this->open_signal.signaler.empty()) {
    return false;
  }

  const double signaled_price = current_price(this->open_signal.signaled);
  const double converted_signaler_price_ =
      converted_signaler_price(this->open_signal);

  const double price_delta_ratio =
      abs(converted_signaler_price_ - signaled_price) / signaled_price;

  if (price_delta_ratio >= 0.001) {
    return true;
  }

  const int time_minimum = 60;
  const bool is_persistent_signal =
      (std::time(nullptr) - this->open_signal.signaler_trend_started_at) >=
      time_minimum;

  if (price_delta_ratio > 0 && is_persistent_signal) {
    return true;
  }

  return false;
}

#endif
