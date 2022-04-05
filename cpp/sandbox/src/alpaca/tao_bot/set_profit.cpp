#ifndef ALPACA__TAO_BOT_set_profit
#define ALPACA__TAO_BOT_set_profit

#include "compute_profit.cpp" // compute_profit
#include "tao_bot.h"          // Alpaca::TaoBot, order_t, quote_t
#include <algorithm>          // std::max
#include <vector>             // std::vector

void Alpaca::TaoBot::set_profit(order_t *order,
                                const std::vector<quote_t> *quotes_ptr) {
  const double profit = compute_profit(order, &(quotes_ptr->back()));

  order->max_profit = std::max(profit, order->max_profit);
  order->profit = profit;
}

void Alpaca::TaoBot::set_profit(order_t *close_order_,
                                const order_t *open_order_) {
  close_order_->profit = compute_profit(close_order_, open_order_);
}

#endif
