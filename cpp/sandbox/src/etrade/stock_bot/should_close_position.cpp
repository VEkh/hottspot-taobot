#if !defined ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * gear_t
 * order_status_t
 */
#include "stock_bot.h"

bool ETrade::StockBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
    return false;
  }

  gear_t *current_gear_ptr = this->transmission.current_gear();

  if (!current_gear_ptr) {
    return false;
  }

  const double max_loss = this->moving_price_range.max_loss;
  const double min_profit = this->moving_price_range.min_profit;

  const double stop_loss_threshold = 1.2;

  const gear_t current_gear = *current_gear_ptr;

  if (this->open_order.max_profit >= (min_profit / 0.8) &&
      this->open_order.profit < this->open_order.max_profit * 0.8 &&
      this->open_order.profit >= min_profit) {
    return true;
  }

  if (this->is_long_position &&
      this->long_average_sell_buy_ratio >= stop_loss_threshold) {
    return true;
  }

  if (!this->is_long_position &&
      this->long_average_buy_sell_ratio >= stop_loss_threshold) {
    return true;
  }

  if (this->open_order.profit <= -max_loss) {
    return true;
  }

  return false;
}

#endif
