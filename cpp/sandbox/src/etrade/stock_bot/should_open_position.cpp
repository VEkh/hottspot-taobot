#ifndef ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

/*
 * ETrade::StockBot
 * fmt
 * position_t
 */
#include "stock_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats
#include "lib/utils/integer.cpp"            // utils::integer_
#include <time.h>                           // time, time_t

bool ETrade::StockBot::should_open_position() {
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

  const closed_positions_stats_t stats = build_closed_positions_stats();

  const double long_door_threshold = 1.35;
  const double short_door_threshold = 1.5;

  if ((this->long_average_buy_sell_ratio >= long_door_threshold &&
       this->short_average_buy_sell_ratio >= short_door_threshold) ||
      (this->long_average_sell_buy_ratio >= long_door_threshold &&
       this->short_average_sell_buy_ratio >= short_door_threshold)) {
    this->is_long_position =
        this->long_average_buy_sell_ratio >= long_door_threshold;

    return true;
  }

  return false;
}

#endif
