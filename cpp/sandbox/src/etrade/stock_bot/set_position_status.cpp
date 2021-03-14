#if !defined ETRADE__STOCK_BOT_set_position_status
#define ETRADE__STOCK_BOT_set_position_status

#include "set_status.cpp" // set_status
#include "stock_bot.h"    // ETrade::StockBot

void ETrade::StockBot::set_position_status() {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  set_status(this->open_order_ptr);
  set_status(this->close_order_ptr);
}

#endif
