#ifndef OANDA__TAO_BOT_has_already_stopped_profit
#define OANDA__TAO_BOT_has_already_stopped_profit

#include "tao_bot.h" // Oanda::TaoBot, order_t

bool Oanda::TaoBot::has_already_stopped_profit() {
  if (this->closed_positions.empty()) {
    return false;
  }

  const order_t close_order_ = this->closed_positions.back().close_order;

  if (!close_order_.stop_profit) {
    return false;
  }

  return close_order_.max_profit >= close_order_.stop_profit;
}

#endif
