#ifndef ALPACA__TAO_BOT_is_position_closed
#define ALPACA__TAO_BOT_is_position_closed

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::is_position_closed() {
  return !this->close_order_ptr && !this->hedge_open_order_ptr &&
         !this->hedge_close_order_ptr && !this->open_order_ptr;
}

#endif
