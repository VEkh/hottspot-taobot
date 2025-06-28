// TODO: Decide
#ifndef OANDA__TAO_BOT_execution_strategy
#define OANDA__TAO_BOT_execution_strategy

#include "tao_bot.h" // Oanda::TaoBot, execution_strategy_t
#include <string>    // std::string

Oanda::TaoBot::execution_strategy_t Oanda::TaoBot::execution_strategy() {
  const std::string config = this->api_client.config.execution_strategy;

  if (config == "CONSOLIDATION") {
    return execution_strategy_t::EXECUTION_STRATEGY_CONSOLIDATION;
  }

  if (config == "DYNAMIC") {
    const double dynamic_reverse_percentile_ratio =
        this->api_client.config.dynamic_reverse_percentile_ratio;

    if (!this->open_order_ptr) {
      return execution_strategy_t::EXECUTION_STRATEGY_TREND;
    }

    if (!dynamic_reverse_percentile_ratio) {
      return execution_strategy_t::EXECUTION_STRATEGY_TREND;
    }

    // v0.1
    // if (this->warm_up_candle.body_wick_ratio() <
    //     dynamic_reverse_percentile_ratio) {
    //   return execution_strategy_t::EXECUTION_STRATEGY_CONSOLIDATION;
    // }

    // v0.2
    if (!this->closed_positions.empty()) {
      return execution_strategy_t::EXECUTION_STRATEGY_CONSOLIDATION;
    }

    const double max_profit_warm_up_ratio =
        this->open_order_ptr->max_profit /
        this->open_order_ptr->day_candle.range();

    if (max_profit_warm_up_ratio < dynamic_reverse_percentile_ratio) {
      return execution_strategy_t::EXECUTION_STRATEGY_CONSOLIDATION;
    }

    return execution_strategy_t::EXECUTION_STRATEGY_TREND;
  }

  if (config == "TREND") {
    return execution_strategy_t::EXECUTION_STRATEGY_TREND;
  }

  return execution_strategy_t::EXECUTION_STRATEGY_TREND;
}

#endif
