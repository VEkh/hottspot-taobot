#ifndef OANDA__TAO_BOT_reset_orders
#define OANDA__TAO_BOT_reset_orders

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::reset_orders() {
  this->close_order_ptr = nullptr;
  this->open_order_ptr = nullptr;
}

#endif
