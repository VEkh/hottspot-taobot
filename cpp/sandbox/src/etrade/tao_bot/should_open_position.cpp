#ifndef ETRADE__TAO_BOT_should_open_position
#define ETRADE__TAO_BOT_should_open_position

#include "candlesticks_in_direction.cpp" // candlesticks_in_direction
#include "lib/utils/time.cpp"            // ::utils::time_
#include "tao_bot.h"                     // ETrade::TaoBot, order_action_t
#include <stdlib.h>                      // rand, srand

bool ETrade::TaoBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  if (!this->average_tick_price_delta) {
    return false;
  }

  srand(::utils::time_::epoch("nanoseconds"));
  const bool coin[] = {false, true};
  const int side_index = rand() % 2;

  this->is_long_position = coin[side_index];

  return true;
}

bool ETrade::TaoBot::should_open_position(const order_action_t order_action) {
  const double long_door_threshold = 1.5;
  const double short_door_threshold = 1.75;

  if (candlesticks_in_direction(order_action)) {
    return true;
  }

  switch (order_action) {
  case order_action_t::BUY: {
    return this->long_average_buy_sell_ratio >= long_door_threshold &&
           this->short_average_buy_sell_ratio >= short_door_threshold;
  }

  case order_action_t::SELL_SHORT: {
    return this->long_average_sell_buy_ratio >= long_door_threshold &&
           this->short_average_sell_buy_ratio >= short_door_threshold;
  }
  }

  return false;
}

#endif
