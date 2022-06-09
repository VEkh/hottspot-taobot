#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "converted_signaler_price.cpp" // converted_signaler_price
#include "current_price.cpp"            // current_price
#include "hedge_symbol.cpp"             // hedge_symbol
#include "tao_bot.h"                    // Alpaca::TaoBot, quote_t
#include <ctime>                        // std::time
#include <math.h>                       // abs

bool Alpaca::TaoBot::should_open_position(const order_t *order_ptr) {
  if (order_ptr) {
    return false;
  }

  if (!this->price_movements[this->symbol]
           .short_term_three_minute_one_second_variance.average) {
    return false;
  }

  const std::vector<quote_t> quotes_ = this->quotes[this->symbol];
  const bool is_price_moving =
      quotes_.back().price != quotes_.at(quotes_.size() - 2).price;

  if (!is_price_moving) {
    return false;
  }

  return true;
}

bool Alpaca::TaoBot::should_open_position(const signal_t &signal) {
  const double signaled_price = current_price(signal.signaled);
  const double converted_signaler_price_ = converted_signaler_price(signal);

  const double price_delta_ratio =
      abs(converted_signaler_price_ - signaled_price) / signaled_price;

  const int time_minimum = 0.5 * 60;
  const bool is_persistent_signal =
      (std::time(nullptr) - signal.signaler_trend_started_at) >= time_minimum;

  return price_delta_ratio >= 0.0003 && is_persistent_signal;
}

#endif
