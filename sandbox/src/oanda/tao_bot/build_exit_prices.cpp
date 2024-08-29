#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Oanda::TaoBot
#include <algorithm> // std::min
#include <math.h>    // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double execution_mid = this->open_order_ptr->execution_price;
  const order_action_t action = this->open_order_ptr->action;

  const double reversal_delta = action == order_action_t::BUY
                                    ? entry_reversal_mid - execution_mid
                                    : execution_mid - entry_reversal_mid;

  double stop_loss = std::min(-0.00001, reversal_delta);
  double stop_profit = 0.0;

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
