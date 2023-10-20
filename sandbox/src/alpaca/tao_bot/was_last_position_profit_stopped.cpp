#ifndef ALPACA__TAO_BOT_was_last_position_profit_stopped
#define ALPACA__TAO_BOT_was_last_position_profit_stopped

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::was_last_position_profit_stopped() {
  if (this->closed_positions.empty()) {
    return false;
  }

  const position_t last_position = this->closed_positions.back();

  if (last_position.close_order.profit < 0) {
    return false;
  }

  return last_position.open_order.max_profit >= this->exit_prices.min_profit;
};

#endif
