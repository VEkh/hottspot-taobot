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

  gear_t current_gear = *current_gear_ptr;

  if (current_gear == gear_t::N && this->open_order.profit > 0) {
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
