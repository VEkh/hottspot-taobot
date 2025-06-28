#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h" // Oanda::TaoBot, execution_strategy_t // TODO: Decide
#include <algorithm> // std::max
#include <math.h>    // abs

#include "execution_strategy.cpp" // TODO: Decide

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double execution_price = this->open_order_ptr->execution_price;
  const order_action_t action = this->open_order_ptr->action;

  const double reversal_delta = abs(entry_reversal_mid - execution_price);

  // TODO: Decide
  double stop_loss = -std::max(0.00001, reversal_delta) -
                     this->api_client.config.stop_loss_padding_ratio *
                         this->day_candle.range();

  // const double stop_loss =
  //     -std::max(0.00001, reversal_delta) -
  //     this->STOP_LOSS_PADDING_RATIO * this->day_candle.range();

  // TODO: Decide
  double stop_profit = 0.0;

  if (this->api_client.config.should_stop_profit) {
    const double execution_price_percentile =
        day_range_percentile(this->open_order_ptr->day_candle, execution_price);

    const double inv_execution_price_percentile =
        abs(100.0 - execution_price_percentile);

    const double max_percentile_delta =
        std::max(execution_price_percentile, inv_execution_price_percentile) /
        100.0;

    stop_profit =
        this->open_order_ptr->day_candle.range() * max_percentile_delta;
  }

  // TODO: Decide
  if (this->api_client.config.execution_strategy == "DYNAMIC" &&
      execution_strategy() == execution_strategy_t::EXECUTION_STRATEGY_TREND) {
    stop_profit = 0.0;
  }

  // TODO: Decide
  // v0.1
  // stop_profit *= this->api_client.config.stop_profit_multiplier;

  // v0.2
  if (this->api_client.config.stop_profit_multiplier != 1.0 &&
      this->api_client.config.margin_normalization_base_price_action) {
    const double normalization_base =
        this->api_client.config.margin_normalization_base_price_action * 100.0;

    const double multiplier =
        normalization_base / this->warm_up_candle.range_open_percent();

    stop_profit *= std::max(1.0, multiplier);
  }

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
