#ifndef ALPACA__TAO_BOT_set_profit
#define ALPACA__TAO_BOT_set_profit

#include "compute_profit.cpp"       // compute_profit
#include "open_position_profit.cpp" // open_position_profit
#include "tao_bot.h"                // Alpaca::TaoBot, order_t
#include <algorithm>                // std::max, std::min

void Alpaca::TaoBot::set_profit(order_t *order) {
  const double profit = compute_profit(order, &(this->quotes.front()));

  const double position_profit = open_position_profit(this->open_order_ptr);

  order->max_position_profit =
      std::max(order->max_position_profit, position_profit);

  order->max_profit = std::max(profit, order->max_profit);
  order->min_profit = std::min(profit, order->min_profit);
  order->profit = profit;
  order->stop_loss = this->exit_prices.stop_loss;
  order->stop_profit = this->exit_prices.stop_profit;

  if (profit == order->max_profit) {
    order->max_profit_at = this->current_epoch;
  }

  if (profit == order->min_profit) {
    order->min_profit_at = this->current_epoch;
  }
}

void Alpaca::TaoBot::set_profit(order_t *close_order_, order_t *open_order_) {
  close_order_->profit = compute_profit(close_order_, open_order_);

  close_order_->max_position_profit = open_order_->max_position_profit;
  close_order_->max_profit = open_order_->max_profit;
  close_order_->max_profit_at = open_order_->max_profit_at;
  close_order_->min_profit = open_order_->min_profit;
  close_order_->min_profit_at = open_order_->min_profit_at;
  close_order_->stop_loss = open_order_->stop_loss;
  close_order_->stop_profit = open_order_->stop_profit;
}

#endif
