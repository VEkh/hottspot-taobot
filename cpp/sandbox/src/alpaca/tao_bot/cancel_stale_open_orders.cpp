#ifndef ALPACA__TAO_BOT_cancel_stale_open_orders
#define ALPACA__TAO_BOT_cancel_stale_open_orders

#include "cancel_stale_open_order.cpp" // cancel_stale_open_order
#include "tao_bot.h"                   // Alpaca::TaoBot, order_status_t

void Alpaca::TaoBot::cancel_stale_open_orders() {
  cancel_stale_open_order(this->api_client, this->open_order_ptr);
  cancel_stale_open_order(this->api_client, this->hedge_open_order_ptr);
}

#endif
