#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

/*
 * ETrade::StockBot
 * quote_t
 */
#include "stock_bot.h"

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const double long_entry_threshold = 1.1;

  if (this->long_average_buy_sell_ratio >= long_entry_threshold ||
      this->long_average_sell_buy_ratio >= long_entry_threshold) {
    this->is_long_position =
        this->long_average_buy_sell_ratio >= long_entry_threshold;
    return true;
  }

  return false;
}

#endif
