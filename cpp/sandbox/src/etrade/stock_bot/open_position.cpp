#if !defined ETRADE__STOCK_BOT_open_position
#define ETRADE__STOCK_BOT_open_position

/*
 * order_action_t
 * order_status_t
 * order_type_t
 */
#include "stock_bot.h"

void ETrade::StockBot::open_position() {
  if (this->open_order_ptr) {
    return;
  }

  order_t new_open_order;
  new_open_order.action = order_action_t::BUY;
  new_open_order.quantity = this->quantity;
  new_open_order.symbol = this->symbol;
  new_open_order.type = order_type_t::MARKET;

  order_t new_close_order;
  new_close_order.action = order_action_t::SELL;
  new_close_order.quantity = this->quantity;
  new_close_order.symbol = this->symbol;
  new_close_order.type = order_type_t::MARKET;

  this->close_order = new_close_order;
  this->close_order_ptr = &(this->close_order);
  this->open_order = new_open_order;
  this->open_order_ptr = &(this->open_order);
}

#endif
