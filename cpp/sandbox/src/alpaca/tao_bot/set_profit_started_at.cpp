#ifndef ALPACA__TAO_BOT_set_profit_started_at
#define ALPACA__TAO_BOT_set_profit_started_at

#include "is_hedging.cpp"           // is_hedging
#include "open_position_profit.cpp" // open_position_profit
#include "tao_bot.h"                // Alpaca::TaoBot, order_status_t
#include <ctime>                    // std::time
#include <math.h>                   // INFINITY

void Alpaca::TaoBot::set_profit_started_at() {
  if (!(this->open_order_ptr &&
        this->open_order_ptr->status == order_status_t::ORDER_FILLED)) {
    this->profit_started_at = INFINITY;
    return;
  }

  if (is_hedging() &&
      !(this->hedge_open_order_ptr &&
        this->hedge_open_order_ptr->status == order_status_t::ORDER_FILLED)) {
    this->profit_started_at = INFINITY;
    return;
  }

  const double profit =
      open_position_profit(this->open_order_ptr, this->hedge_open_order_ptr);

  if (profit < 0) {
    this->profit_started_at = INFINITY;
    return;
  }

  if (profit > 0 && this->profit_started_at != INFINITY) {
    return;
  }

  const std::time_t now = std::time(nullptr);
  this->profit_started_at = (int)now;
}

#endif
