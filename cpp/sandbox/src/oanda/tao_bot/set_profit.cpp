#ifndef OANDA__TAO_BOT_set_profit
#define OANDA__TAO_BOT_set_profit

#include "compute_profit.cpp" // compute_profit
#include "tao_bot.h"          // Oanda::TaoBot, order_t
#include <algorithm>          // std::max

void Oanda::TaoBot::set_profit(order_t *order) {
  const double profit = compute_profit(order, &(this->quotes.back()));

  order->max_profit = std::max(profit, order->max_profit);
  order->profit = profit;
}

void Oanda::TaoBot::set_profit(order_t *close_order_,
                               const order_t *open_order_) {
  close_order_->profit = compute_profit(close_order_, open_order_);
}

#endif
