#ifndef ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

/*
 * BUY_SELL_RATIO_DOOR_THRESHOLD
 * ETrade::StockBot
 * fmt
 * position_t
 */
#include "stock_bot.h"

#include "lib/utils/integer.cpp" // utils::integer_
#include <time.h>                // time, time_t

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  if (!this->closed_positions.empty()) {
    time_t now;
    time(&now);

    const position_t last_position = this->closed_positions.back();

    const int seconds_since_close = now - last_position.close_timestamp;

    if (seconds_since_close < 45) {
      std::cout << fmt.bold << fmt.yellow << std::endl;
      std::cout << "🤚🏾 Throttle engaged. Time remaining: "
                << utils::integer_::seconds_to_clock(45 - seconds_since_close)
                << fmt.reset << std::endl;
      return false;
    }
  }

  const double short_door_threshold = 1.5;

  if ((this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD &&
       this->short_average_buy_sell_ratio >= short_door_threshold) ||
      (this->long_average_sell_buy_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD &&
       this->short_average_sell_buy_ratio >= short_door_threshold)) {
    this->is_long_position =
        this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD;

    return true;
  }

  return false;
}

#endif
