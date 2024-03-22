#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h"      // Alpaca::TaoBot
#include "volatility.cpp" // volatility
#include <algorithm>      // std::max, std::min
#include <math.h>         // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double trailing_stop_profit_ratio = 1 / 1.1;

  double stop_loss_ratio = this->api_client.config.stop_loss_ratio;
  double stop_profit_ratio = this->api_client.config.stop_profit_ratio;

  if (this->api_client.config.stop_loss_ratios[this->symbol]) {
    stop_loss_ratio = this->api_client.config.stop_loss_ratios[this->symbol];
  }

  const double config_stop_loss = stop_loss_ratio * static_one_sec_variance;
  const double execution_mid = this->open_order_ptr->execution_price;
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;

  double stop_loss = stop_loss_ratio * static_one_sec_variance;

  const double stop_loss_percent = this->api_client.config.stop_loss_percent;

  // TODO: Decide
  if (stop_loss_percent) {
    stop_loss = (stop_loss_percent / 100.0) * execution_mid;
  }

  // TODO: Decide
  if (this->api_client.config.should_await_reversal_indicator &&
      this->api_client.config.is_stop_loss_dynamic) {
    const double reversal_delta = abs(execution_mid - entry_reversal_mid);

    const double dynamic_loss =
        reversal_delta ? reversal_delta : abs(stop_loss);

    stop_loss = -dynamic_loss;
  }

  const double same_peak_padding = 0.02;
  stop_loss -= same_peak_padding;

  if (this->api_client.config.stop_profit_ratios[this->symbol]) {
    stop_profit_ratio =
        this->api_client.config.stop_profit_ratios[this->symbol];
  }

  double stop_profit = abs(stop_profit_ratio * stop_loss);

  if (this->api_client.config.stop_profit_max_ratio) {
    const double profit_ratio = this->api_client.config.stop_profit_max_ratio;

    stop_profit = std::min(stop_profit, abs(profit_ratio * config_stop_loss));
  }

  // TODO: Decide
  if (this->is_trending && this->api_client.config.should_hold_trend_profit) {
    stop_profit = 0;
  }

  if (this->api_client.config.deficit_reclaim_ratio) {
    const double asset_deficit =
        abs(this->performance.current_balance - this->performance.max_balance);

    const double deficit_profit =
        1.04 * (asset_deficit / this->open_order_ptr->quantity);

    if (asset_deficit && deficit_profit >= abs(config_stop_loss)) {
      stop_profit = deficit_profit;
    }
  }

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
