#ifndef ETRADE__TAO_BOT_profit_percentage
#define ETRADE__TAO_BOT_profit_percentage

#include "tao_bot.h" // ETrade::TaoBot, order_t

double ETrade::TaoBot::profit_percentage(const order_t *order_ptr) {
  if (!order_ptr) {
    return 0.0;
  }

  if (!order_ptr->execution_price) {
    return 0.0;
  }

  return 100 * (order_ptr->profit / order_ptr->execution_price);
}

#endif
