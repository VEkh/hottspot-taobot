#ifndef ALPACA__TAO_BOT_close_positions
#define ALPACA__TAO_BOT_close_positions

#include "close_position.cpp" // close_position
#include "is_hedging.cpp"     // is_hedging
#include "tao_bot.h"          // Alpaca::TaoBot

void Alpaca::TaoBot::close_positions() {
  close_position(this->api_client, this->close_order_ptr, this->open_order_ptr);

  close_position(this->api_client, this->hedge_close_order_ptr,
                 this->hedge_open_order_ptr);
}

#endif
