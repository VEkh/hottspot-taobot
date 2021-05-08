#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

/*
 * BUY_SELL_RATIO_DOOR_THRESHOLD
 * ETrade::StockBot
 * quote_t
 */
#include "stock_bot.h"

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const double short_door_threshold = 1.35;

  if ((this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD &&
       this->short_average_buy_sell_ratio >= short_door_threshold) ||
      (this->long_average_sell_buy_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD &&
       this->short_average_sell_buy_ratio >= short_door_threshold)) {
    const double current_price = this->quotes.back().current_price;

    this->is_long_position =
        this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD;

    return true;
  }

  return false;
}

#endif
