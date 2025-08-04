#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h" // Oanda::TaoBot, order_action_t, stop_profit_type_t // TODO: Decide
#include <algorithm> // std::max
#include <math.h>    // abs

#include "stop_profit_type.cpp" // stop_profit_type // TODO: Decide

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

  const double stop_profit_version_ =
      this->api_client.config.stop_profit_version;

  double stop_profit = 0.0;

  if (this->api_client.config.should_stop_profit) {
    const stop_profit_type_t stop_profit_type_ =
        stop_profit_type(day_candle_, execution_price);

    // v0.1, v0.2 (STOP_PROFIT_CROSS_RANGE), v0.3 (STOP_PROFIT_CROSS_RANGE)
    const double execution_price_percentile =
        day_range_percentile(day_candle_, execution_price);

    const double inv_execution_price_percentile =
        abs(100.0 - execution_price_percentile);

    const double max_percentile_delta =
        std::max(execution_price_percentile, inv_execution_price_percentile) /
        100.0;

    stop_profit = day_candle_.range() * max_percentile_delta;

    if (stop_profit_type_ == stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE) {
      // v0.2
      if (stop_profit_version_ == 0.2) {
        stop_profit = 0.0;
      }

      // v0.3
      if (stop_profit_version_ == 0.3 &&
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

        stop_profit = max_stop_profit;
      }
    }
  }

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
