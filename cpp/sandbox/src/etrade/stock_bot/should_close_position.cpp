#if !defined ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * gear_t
 * order_status_t
 */
#include "stock_bot.h"
#include <time.h> // time, time_t

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
  const double short_term_loss_threshold = 1.0;
  const double stop_loss_threshold = 1.1;

  const gear_t current_gear = *current_gear_ptr;
  time_t now;
  time(&now);

  if (now - this->open_order.max_profit_timestamp >= 30) {
    return true;
  }

  if (this->is_long_position &&
      this->long_average_buy_sell_ratio < stop_loss_threshold) {
    return true;
  }

  if (!this->is_long_position &&
      this->long_average_sell_buy_ratio < stop_loss_threshold) {
    return true;
  }

  if (current_gear == gear_t::D && this->open_order.profit > 0) {
    if (this->is_long_position &&
        this->long_average_buy_sell_ratio < stop_loss_threshold) {
      return true;
    }

    if (!this->is_long_position &&
        this->long_average_sell_buy_ratio < stop_loss_threshold) {
      return true;
    }
  }

  if (this->open_order.profit <= -max_loss) {
    return true;
  }

  return false;
}

#endif
