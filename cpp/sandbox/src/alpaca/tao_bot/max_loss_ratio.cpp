#ifndef ALPACA__TAO_BOT_max_loss_ratio
#define ALPACA__TAO_BOT_max_loss_ratio

#include "lib/utils/float.cpp" // ::utils::float_
#include "tao_bot.h"           // Alpaca::TaoBot, order_t
#include "volatility.cpp"      // volatility

double Alpaca::TaoBot::max_loss_ratio(const order_t *order_ptr) {
  return -::utils::float_::sigmoid(0.005, 0.0009, volatility(order_ptr), 1.25,
                                   4.0);
}

#endif
