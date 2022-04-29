#ifndef ALPACA__TAO_BOT_max_loss_ratio
#define ALPACA__TAO_BOT_max_loss_ratio

#include "tao_bot.h"      // Alpaca::TaoBot, order_t
#include "volatility.cpp" // volatility

double Alpaca::TaoBot::max_loss_ratio(const order_t *order_ptr) {
  return -::utils::float_::sigmoid(0.0015, 0.001, volatility(order_ptr), 5,
                                   1.5);
}

#endif
