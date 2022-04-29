#ifndef ALPACA__TAO_BOT_take_profit_after
#define ALPACA__TAO_BOT_take_profit_after

#include "tao_bot.h"      // Alpaca::TaoBot, order_t
#include "volatility.cpp" // volatility

int Alpaca::TaoBot::take_profit_after(const order_t *order_ptr) {
  return ::utils::float_::sigmoid(30, 5, volatility(order_ptr), -5, 1.25);
}

#endif
