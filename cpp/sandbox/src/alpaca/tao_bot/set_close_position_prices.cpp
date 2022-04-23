#ifndef ALPACA__TAO_BOT_set_close_position_prices
#define ALPACA__TAO_BOT_set_close_position_prices

#include "set_close_order_prices.cpp" // set_close_order_prices
#include "tao_bot.h"                  // Alpaca::TaoBot

void Alpaca::TaoBot::set_close_position_prices() {
  set_close_order_prices(this->api_client, this->close_order_ptr,
                         this->open_order_ptr);
}

#endif
