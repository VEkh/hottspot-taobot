#ifndef ALPACA__TAO_BOT_profit_percentage
#define ALPACA__TAO_BOT_profit_percentage

#include "tao_bot.h" // Alpaca::TaoBot, order_t
#include <string>    // std::string

double Alpaca::TaoBot::profit_percentage(const order_t *order_ptr,
                                         const std::string key = "profit") {
  if (!order_ptr) {
    return 0.0;
  }

  if (!order_ptr->execution_price) {
    return 0.0;
  }

  double profit = order_ptr->profit;

  if (key == "max_profit") {
    profit = order_ptr->max_profit;
  } else if (key == "min_profit") {
    profit = order_ptr->min_profit;
  }

  return 100 * (profit / order_ptr->execution_price);
}

#endif
