#ifndef ALPACA__TAO_BOT_close_positions
#define ALPACA__TAO_BOT_close_positions

#include "close_position.cpp" // close_position
#include "tao_bot.h"          // Alpaca::TaoBot

void Alpaca::TaoBot::close_positions() {
  close_position(this->api_client, this->close_order_ptr, this->open_order_ptr);
}

#endif
