#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double execution_mid = this->open_order_ptr->execution_price;
  const double same_peak_padding = 0.02;
  const double stop_profit = 0.0;

  const double reversal_delta = abs(execution_mid - entry_reversal_mid);

  double stop_loss = -(reversal_delta ? reversal_delta : same_peak_padding);

  stop_loss -= same_peak_padding;

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
