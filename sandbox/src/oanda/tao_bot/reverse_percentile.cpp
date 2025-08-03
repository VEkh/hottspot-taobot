// TODO: Decide
#ifndef OANDA__TAO_BOT_reverse_percentile
#define OANDA__TAO_BOT_reverse_percentile

#include "execution_strategy.cpp"  // execution_strategy // TODO: Decide
#include "stop_profit_version.cpp" // stop_profit_version // TODO: Decide
#include "tao_bot.h"               // Oanda::TaoBot

double Oanda::TaoBot::reverse_percentile() {
  const double default_reverse_percentile =
      this->api_client.config.reverse_percentile;

  const double dynamic_reverse_percentile =
      this->api_client.config.dynamic_reverse_percentile;

  const double dynamic_reverse_percentile_ratio =
      this->api_client.config.dynamic_reverse_percentile_ratio;

  if (!dynamic_reverse_percentile) {
    return default_reverse_percentile;
  }

  if (!this->open_order_ptr) {
    return default_reverse_percentile;
  }

  // Version 0.1
  // if (!this->closed_positions.empty()) {
  //   return dynamic_reverse_percentile;
  // }

  // const double max_profit_warm_up_ratio =
  //     this->open_order_ptr->max_profit /
  //     this->open_order_ptr->day_candle.range();

  // if (max_profit_warm_up_ratio < dynamic_reverse_percentile_ratio) {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // Version 0.11
  // const double max_profit_warm_up_ratio =
  //     this->open_order_ptr->max_profit / this->day_candle.range();

  // if (max_profit_warm_up_ratio < dynamic_reverse_percentile_ratio) {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // Version 0.12
  // if (!this->closed_positions.empty()) {
  //   return dynamic_reverse_percentile;
  // }

  // const double max_profit_warm_up_ratio =
  //     this->open_order_ptr->max_profit / this->day_candle.range();

  // if (max_profit_warm_up_ratio < dynamic_reverse_percentile_ratio) {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // Version 0.2
  // if (!this->closed_positions.empty()) {
  //   return dynamic_reverse_percentile;
  // }

  // if (!dynamic_reverse_percentile_ratio) {
  //   return default_reverse_percentile;
  // }

  // const double warm_up_range_open_percent =
  //     this->open_order_ptr->day_candle.range_open_percent();

  // if (warm_up_range_open_percent >= dynamic_reverse_percentile_ratio * 100.0)
  // {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // // Version 0.3
  // if (!dynamic_reverse_percentile_ratio) {
  //   return default_reverse_percentile;
  // }

  // const double warm_up_range_open_percent =
  //     this->open_order_ptr->day_candle.range_open_percent();

  // if (warm_up_range_open_percent >= dynamic_reverse_percentile_ratio * 100.0)
  // {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // Version 0.4
  // if (!dynamic_reverse_percentile_ratio) {
  //   return default_reverse_percentile;
  // }

  // if (this->day_candle.range_open_percent() >=
  //     dynamic_reverse_percentile_ratio * 100.0) {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // Version 0.5
  // if (!dynamic_reverse_percentile_ratio) {
  //   return default_reverse_percentile;
  // }

  // if (this->warm_up_candle.body_wick_ratio() <
  //     dynamic_reverse_percentile_ratio) {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // Version 0.51
  // if (!dynamic_reverse_percentile_ratio) {
  //   return default_reverse_percentile;
  // }

  // if (!this->closed_positions.empty()) {
  //   return dynamic_reverse_percentile;
  // }

  // if (this->warm_up_candle.body_wick_ratio() <
  //     dynamic_reverse_percentile_ratio) {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // Version 0.6
  // if (this->market_availability.session_count % 2 == 1) {
  //   return dynamic_reverse_percentile;
  // }

  // return default_reverse_percentile;

  // Version 0.7
  // if (this->open_order_ptr->max_profit >= abs(this->exit_prices.stop_loss)) {
  //   return dynamic_reverse_percentile;
  // }

  // Version 0.8
  if (execution_strategy() == execution_strategy_t::EXECUTION_STRATEGY_TREND) {
    if (stop_profit_version() == 0.2 &&
        this->open_order_ptr->max_profit >= abs(this->exit_prices.stop_loss)) {
      return dynamic_reverse_percentile;
    }

    return default_reverse_percentile;
  }

  if (execution_strategy() ==
      execution_strategy_t::EXECUTION_STRATEGY_CONSOLIDATION) {
    return dynamic_reverse_percentile;
  }

  return default_reverse_percentile;
}

#endif
