#ifndef ALPACA__TAO_BOT_set_open_position_prices
#define ALPACA__TAO_BOT_set_open_position_prices

#include "set_open_order_prices.cpp" // set_open_order_prices
#include "tao_bot.h"                 // Alpaca::TaoBot, order_status_t

void Alpaca::TaoBot::set_open_position_prices() {
  set_open_order_prices(this->api_client, this->open_order_ptr);
  set_open_order_prices(this->hedge_api_client, this->hedge_open_order_ptr);
}

#endif
