#if !defined ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * gear_t
 * order_status_t
 */
#include "stock_bot.h"

#include "profit_percentage.cpp" // profit_percentage

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

  const double max_loss_percentage = 0.5;
  const double min_profit_percentage = 0.05;
  const double profit_percent = profit_percentage(this->open_order_ptr);
  const double short_door_threshold = 1.0;
  const double stop_loss_threshold = 1.2;

  const gear_t current_gear = *current_gear_ptr;

  if (this->is_long_position) {
    if (profit_percent >= min_profit_percentage &&
        this->short_average_sell_buy_ratio >= short_door_threshold) {
      return true;
    }

    if (this->long_average_sell_buy_ratio >= stop_loss_threshold) {
      return true;
    }
  }

  if (!this->is_long_position) {
    if (profit_percent >= min_profit_percentage &&
        this->short_average_buy_sell_ratio >= short_door_threshold) {
      return true;
    }

    if (this->long_average_buy_sell_ratio >= stop_loss_threshold) {
      return true;
    }
  }

  if (profit_percent < -max_loss_percentage) {
    return true;
  }

  return false;
}

#endif
