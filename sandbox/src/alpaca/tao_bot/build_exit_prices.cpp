#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double execution_mid = this->open_order_ptr->execution_price;
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double stop_profit = 0.0;

  double stop_loss = 0.0;

  if (this->api_client.config.should_await_reversal_indicator) {
    const double reversal_delta = abs(execution_mid - entry_reversal_mid);

    const double dynamic_loss =
        reversal_delta ? reversal_delta : abs(stop_loss);

    stop_loss = -dynamic_loss;
  }

  const double same_peak_padding = 0.02;
  stop_loss -= same_peak_padding;

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
