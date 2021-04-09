#if !defined ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * fmt
 * order_status_t
 * quote_t
 * sma_t
 */
#include "stock_bot.h"

bool ETrade::StockBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
    return false;
  }

  const double long_exit_threshold = 1.0;

  if (!this->has_direction_reversed && this->open_order.profit > 0) {
    if (this->is_long_position) {
      return long_average_buy_sell_ratio <= long_exit_threshold;
    } else {
      return long_average_sell_buy_ratio <= long_exit_threshold;
    }
  }

  if (this->has_direction_reversed && !this->has_direction_returned) {
    return false;
  }

  if (this->is_long_position) {
    return long_average_buy_sell_ratio <= long_exit_threshold;
  } else {
    return long_average_sell_buy_ratio <= long_exit_threshold;
  }

  return false;
}

#endif
