#ifndef ALPACA__TAO_BOT_set_position_status
#define ALPACA__TAO_BOT_set_position_status

#include "is_hedging.cpp"         // is_hedging
#include "is_position_closed.cpp" // is_position_closed
#include "set_status.cpp"         // set_status
#include "tao_bot.h"              // Alpaca::TaoBot

void Alpaca::TaoBot::set_position_status() {
  if (is_position_closed()) {
    return;
  }

  set_status(this->open_order_ptr, &this->api_client);
  set_status(this->close_order_ptr, &this->api_client);

  if (is_hedging()) {
    set_status(this->hedge_open_order_ptr, &this->hedge_api_client);
    set_status(this->hedge_close_order_ptr, &this->hedge_api_client);
  }
}

#endif
