#ifndef ALPACA__TAO_BOT_should_terminate
#define ALPACA__TAO_BOT_should_terminate

#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "tao_bot.h"                    // Alpaca::TaoBot, order_status_t

bool Alpaca::TaoBot::should_terminate() {
  if (!is_end_of_trading_period()) {
    return false;
  }

  if (!this->close_order_ptr) {
    return true;
  }

  return this->close_order.status == order_status_t::ORDER_FILLED;
}

#endif
