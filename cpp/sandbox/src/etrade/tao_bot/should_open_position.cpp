#ifndef ETRADE__TAO_BOT_should_open_position
#define ETRADE__TAO_BOT_should_open_position

/*
 * ETrade::TaoBot
 * fmt
 * order_action_t
 * position_t
 */
#include "tao_bot.h"

#include "candlesticks_in_direction.cpp" // candlesticks_in_direction
#include "lib/utils/integer.cpp"         // utils::integer_
#include <time.h>                        // time, time_t

bool ETrade::TaoBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  if (!this->FLAG_MARTINGALE && !this->closed_positions.empty()) {
    time_t now;
    time(&now);

    const position_t last_position = this->closed_positions.back();

    const int seconds_since_close = now - last_position.close_timestamp;
    const int throttle_time_limit = 30;

    if (seconds_since_close < throttle_time_limit) {
      std::cout << fmt.bold << fmt.yellow;
      std::cout << "🛑 Throttle engaged. Time remaining: "
                << utils::integer_::seconds_to_clock(throttle_time_limit -
                                                     seconds_since_close);
      std::cout << fmt.reset << std::endl << std::endl;
      return false;
    }
  }

  if (should_open_position(order_action_t::BUY)) {
    this->is_long_position = true;

    return true;
  }

  if (should_open_position(order_action_t::SELL_SHORT)) {
    this->is_long_position = false;

    return true;
  }

  return false;
}

bool ETrade::TaoBot::should_open_position(order_action_t order_action) {
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
