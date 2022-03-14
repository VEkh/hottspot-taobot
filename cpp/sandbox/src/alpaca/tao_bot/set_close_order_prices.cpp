#ifndef ALPACA__TAO_BOT_set_close_order_prices
#define ALPACA__TAO_BOT_set_close_order_prices

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "set_execution_price.cpp"  // set_execution_price
#include "set_profit.cpp"           // set_profit
#include "tao_bot.h"                // Alpaca::TaoBot, order_status_t, order_t

void Alpaca::TaoBot::set_close_order_prices(Alpaca::Client &api_client_ref,
                                            order_t *close_order_ptr_,
                                            order_t *open_order_ptr_) {
  if (!close_order_ptr_ || !open_order_ptr_) {
    return;
  }

  if (close_order_ptr_->status != order_status_t::ORDER_FILLED) {
    return;
  }

  set_execution_price(api_client_ref, close_order_ptr_);
  set_profit(open_order_ptr_, close_order_ptr_);
}

#endif
