#if !defined ETRADE__STOCK_BOT_reset_position
#define ETRADE__STOCK_BOT_reset_position

/*
 * ETrade::StockBot
 * order_status_t
 */
#include "stock_bot.h"

void ETrade::StockBot::reset_position() {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  if (this->open_order.status != order_status_t::ORDER_EXECUTED ||
      this->close_order.status != order_status_t::ORDER_EXECUTED) {
    return;
  }

  this->close_order_ptr = nullptr;
  this->open_order_ptr = nullptr;
}

#endif
