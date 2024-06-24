#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double execution_mid = this->open_order_ptr->execution_price;
  const double peak_padding_cents = 0.02;
  const order_action_t action = this->open_order_ptr->action;

  const double reversal_delta = action == order_action_t::BUY
                                    ? entry_reversal_mid - execution_mid
                                    : execution_mid - entry_reversal_mid;

  double stop_loss = reversal_delta ? reversal_delta : peak_padding_cents;
  double stop_profit = 0.0;

  // TODO: Decide
  if (!this->closed_positions.empty() &&
      this->api_client.config.peak_padding_ratio) {
    stop_loss -=
        this->api_client.config.peak_padding_ratio * this->day_candle.range();
  } else {
    stop_loss -= peak_padding_cents;
  }

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
