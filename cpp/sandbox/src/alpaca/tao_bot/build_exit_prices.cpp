#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <map>       // std::map
#include <math.h>    // abs
#include <string>    // std::string

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->one_sec_variance_avgs.running;

  const int max_loss_coefficient = -62.5;
  const double trailing_stop_profit_ratio = 1 / 1.1;
  double stop_profit_stop_loss_ratio = 2.5;

  if (this->backtest.is_active) {
    std::map<std::string, double> ratios = {
        {"backtest_no_stop_profit", 99999.0},
        {"backtest_1_5", 1.5},
        {"backtest_2_0", 2.0},
        {"backtest_2_25", 2.25},
        {"backtest_2_5", 2.5},
        {"backtest_2_75", 2.75},
        {"backtest_3_0", 3},
    };

    const double ratio = ratios[this->backtest.config.api_key_id];

    stop_profit_stop_loss_ratio = ratio ? ratio : stop_profit_stop_loss_ratio;
  }

  const double max_loss = max_loss_coefficient * static_one_sec_variance;
  const double stop_profit = abs(stop_profit_stop_loss_ratio * max_loss);

  const double min_profit = stop_profit / trailing_stop_profit_ratio;

  const double trailing_stop_profit =
      this->open_order_ptr->max_profit * trailing_stop_profit_ratio;

  exit_prices_t out = {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };

  return out;
}

#endif
