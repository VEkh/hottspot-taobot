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

  if (this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD ||
      this->long_average_sell_buy_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD) {
    this->is_long_position =
        this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD;

    this->transmission.shift_gear(gear_t::D);

    return true;
  }

  return false;
}

#endif
