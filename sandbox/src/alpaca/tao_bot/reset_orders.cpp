#ifndef ALPACA__TAO_BOT_reset_orders
#define ALPACA__TAO_BOT_reset_orders

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::reset_orders() {
  this->close_order_ptr = nullptr;
  this->open_order_ptr = nullptr;
}

#endif
