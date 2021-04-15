#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

/*
 * BUY_SELL_RATIO_DOOR_THRESHOLD
 * ETrade::StockBot
 * gear_t
 */
#include "stock_bot.h"

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const sma_t simple_moving_average = this->quotes.back().simple_moving_average;

  const double buy_sell_ratio = simple_moving_average.buy_sell_ratio;
  const double sell_buy_ratio = simple_moving_average.sell_buy_ratio;

  const double short_door_threshold = 1.2;

  if ((this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD &&
       buy_sell_ratio >= short_door_threshold) ||
      (this->long_average_sell_buy_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD &&
       sell_buy_ratio >= short_door_threshold)) {
    this->is_long_position =
        this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD;

    this->transmission.shift_gear(gear_t::D);

    return true;
  }

  return false;
}

#endif
