#ifndef OANDA__TAO_BOT_is_position_closed
#define OANDA__TAO_BOT_is_position_closed

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::is_position_closed() {
  return !this->close_order_ptr && !this->open_order_ptr;
}

#endif
