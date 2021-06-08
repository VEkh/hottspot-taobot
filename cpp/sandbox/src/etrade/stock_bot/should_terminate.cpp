#ifndef ETRADE__STOCK_BOT_should_terminate
#define ETRADE__STOCK_BOT_should_terminate

#include "stock_bot.h" // ETrade::StockBot, order_status_t

bool ETrade::StockBot::should_terminate() {
  if (!::utils::time_::is_end_of_day()) {
    return false;
  }

  if (!this->close_order_ptr) {
    return true;
  }

  return this->close_order_ptr &&
         this->close_order.status == order_status_t::ORDER_EXECUTED;
}

#endif
