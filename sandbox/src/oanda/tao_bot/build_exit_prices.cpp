#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h" // Oanda::TaoBot, execution_strategy_t, order_action_t, stop_profit_type_t // TODO: Decide
#include <algorithm> // std::max
#include <math.h>    // abs

#include "execution_strategy.cpp"  // execution_strategy  // TODO: Decide
#include "stop_profit_type.cpp"    // stop_profit_type // TODO: Decide
#include "stop_profit_version.cpp" // stop_profit_version // TODO: Decide

Oanda::TaoBot::exit_prices_t
Oanda::TaoBot::build_exit_prices(build_exit_prices_args_t args) {
  candle_t day_candle_ = args.day_candle;
  const double entry_reversal_mid = args.entry_reversal.mid;
  const double execution_price = args.execution_price;
  const order_action_t action = args.action;

  const double reversal_delta = abs(entry_reversal_mid - execution_price);

  // TODO: Decide
  double stop_loss = -std::max(0.00001, reversal_delta) -
                     this->api_client.config.stop_loss_padding_ratio *
                         this->day_candle.range();

  // const double stop_loss =
  //     -std::max(0.00001, reversal_delta) -
  //     this->STOP_LOSS_PADDING_RATIO * this->day_candle.range();

  // TODO: Decide
  const double stop_profit_version_ = stop_profit_version();
  double stop_profit = 0.0;

  // v0.1
  if (this->api_client.config.should_stop_profit) {
    if (stop_profit_version_ == 0.1 || stop_profit_version_ == 0.5) {
      const double execution_price_percentile =
          day_range_percentile(day_candle_, execution_price);

      const double inv_execution_price_percentile =
          abs(100.0 - execution_price_percentile);

      const double max_percentile_delta =
          std::max(execution_price_percentile, inv_execution_price_percentile) /
          100.0;

      stop_profit = day_candle_.range() * max_percentile_delta;
    }

    // TODO: Decide
    if (stop_profit_version_ == 0.2 &&
        this->api_client.config.execution_strategy == "DYNAMIC" &&
        execution_strategy() ==
            execution_strategy_t::EXECUTION_STRATEGY_TREND) {
      stop_profit = 0.0;
    }

    // TODO: Decide
    if (stop_profit_version_ == 0.3) {
      stop_profit = day_candle_.range() * 0.5;
    }

    // TODO: Decide
    if (stop_profit_version_ == 0.4) {
      stop_profit = 0.0;
    }

    // TODO: Decide
    if ((stop_profit_version_ >= 0.5 && stop_profit_version_ < 0.6) &&
        this->api_client.config.stop_profit_target_price_action) {
      const double target_price_action =
          this->api_client.config.stop_profit_target_price_action;

      const double target_price_action_day_candle_ratio =
          (target_price_action / day_candle_.range_open_percent()) - 1.0;

      const double target_price_action_delta =
          target_price_action_day_candle_ratio * day_candle_.range();

      const double min_stop_profit =
          ((1.0 / (this->TREND_SLIP_PERCENTILE * 0.01) - 1.0)) *
          day_candle_.range();

      const double max_stop_profit =
          std::max(min_stop_profit, target_price_action_delta);

      if (stop_profit_version_ == 0.5 &&
          stop_profit_type(day_candle_, execution_price) ==
              stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE) {
        stop_profit = max_stop_profit;
      } else if (stop_profit_version_ == 0.51) {
        stop_profit = max_stop_profit;
      }
    }
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
