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

  const double short_door_threshold = 1.0;
  const double stop_loss_threshold = 1.25;

  if (this->is_long_position) {
    if (this->open_order.profit > 0 &&
        this->short_average_sell_buy_ratio >= short_door_threshold) {
      return true;
    }

    if (this->long_average_sell_buy_ratio >= stop_loss_threshold) {
      return true;
    }
  }

  if (!this->is_long_position) {
    if (this->open_order.profit > 0 &&
        this->short_average_buy_sell_ratio >= short_door_threshold) {
      return true;
    }

    if (this->long_average_buy_sell_ratio >= stop_loss_threshold) {
      return true;
    }
  }

  gear_t *current_gear_ptr = this->transmission.current_gear();

  if (!current_gear_ptr) {
    return false;
  }

  gear_t current_gear = *current_gear_ptr;

  if (this->transmission.shift_count(gear_t::R) > 1) {
    return true;
  }

  if (current_gear == gear_t::N &&
      this->transmission.shift_count(gear_t::R) > 0 &&
      this->transmission.shift_count(gear_t::D) > 1) {
    return true;
  }

  return false;
}

#endif
