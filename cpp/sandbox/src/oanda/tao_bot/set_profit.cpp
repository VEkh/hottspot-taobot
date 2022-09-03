#ifndef OANDA__TAO_BOT_set_profit
#define OANDA__TAO_BOT_set_profit

#include "compute_profit.cpp"       // compute_profit
#include "open_position_profit.cpp" // open_position_profit
#include "tao_bot.h"                // Oanda::TaoBot, order_t
#include <algorithm>                // std::max
#include <ctime>                    // std::time

void Oanda::TaoBot::set_profit(order_t *order) {
  const double profit = compute_profit(order, &(this->quotes.back()));
  const double position_profit = open_position_profit(this->open_order_ptr);

  order->max_position_profit =
      std::max(order->max_position_profit, position_profit);

  order->max_profit = std::max(profit, order->max_profit);
  order->profit = profit;

  if (profit == order->max_profit) {
    order->max_profit_timesamp = std::time(nullptr);
  }
}

void Oanda::TaoBot::set_profit(order_t *close_order_,
                               const order_t *open_order_) {
  close_order_->profit = compute_profit(close_order_, open_order_);
}

#endif
