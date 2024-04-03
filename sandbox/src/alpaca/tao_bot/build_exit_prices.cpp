#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double trailing_stop_profit_ratio = 1 / 1.1;

  double stop_loss_ratio = this->api_client.config.stop_loss_ratio;
  double stop_profit_ratio = this->api_client.config.stop_profit_ratio;

  const double execution_mid = this->open_order_ptr->execution_price;
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;

  double stop_loss = stop_loss_ratio * static_one_sec_variance;

  if (this->api_client.config.should_await_reversal_indicator) {
    const double reversal_delta = abs(execution_mid - entry_reversal_mid);

    const double dynamic_loss =
        reversal_delta ? reversal_delta : abs(stop_loss);

    stop_loss = -dynamic_loss;
  }

  const double same_peak_padding = 0.02;
  stop_loss -= same_peak_padding;

  double stop_profit = abs(stop_profit_ratio * stop_loss);
  double adjusted_stop_profit = stop_profit / trailing_stop_profit_ratio;

  double trailing_stop_profit =
      this->open_order_ptr->max_profit * trailing_stop_profit_ratio;

  return {
      .stop_loss = stop_loss,
      .stop_profit = adjusted_stop_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };
}

#endif
