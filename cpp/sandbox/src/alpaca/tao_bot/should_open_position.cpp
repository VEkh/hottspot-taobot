#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "tao_bot.h" // Alpaca::TaoBot, quote_t
#include <ctime>     // std::time
#include <math.h>    // abs
#include <vector>    // std:vector

bool Alpaca::TaoBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  if (!this->price_movement.short_term_three_minute_one_second_variance
           .average) {
    return false;
  }

  const std::vector<quote_t> quotes_ = this->quotes;
  const bool is_price_moving =
      quotes_.back().price != quotes_.at(quotes_.size() - 2).price;

  if (!is_price_moving) {
    return false;
  }

  return true;
}

#endif
