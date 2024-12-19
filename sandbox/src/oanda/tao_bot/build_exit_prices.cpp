#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Oanda::TaoBot, stop_profit_type_t // TODO: Decide
#include <algorithm> // std::max
#include <math.h>    // abs

// TODO: Decide
#include "day_range_percentile.cpp" // day_range_percentile
#include "is_trending.cpp"          // is_trending

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double execution_mid = this->open_order_ptr->execution_price;
  const order_action_t action = this->open_order_ptr->action;

  const double reversal_delta = abs(entry_reversal_mid - execution_mid);

  double stop_loss = -std::max(0.00001, reversal_delta);

  // TODO: Decide
  const double stop_loss_padding_ratio =
      this->api_client.config.stop_loss_padding_ratio;

  if (stop_loss_padding_ratio) {
    stop_loss -= stop_loss_padding_ratio * this->day_candle.range();
  }

  double stop_profit = 0.0;

  // TODO: Decide
  if (this->api_client.config.should_stop_profit &&
      (this->open_order_ptr->stop_profit_type ==
           stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE ||
       this->open_order_ptr->stop_profit_type ==
           stop_profit_type_t::STOP_PROFIT_CROSS_RANGE)) {
    const double execution_mid_percentile =
        day_range_percentile(this->open_order_ptr->day_candle, execution_mid);

    const double target_percentile =
        this->api_client.config.stop_profit_target_percentile;

    const double percentile_delta =
        abs(execution_mid_percentile - target_percentile);

    const double inv_percentile_delta =
        abs(execution_mid_percentile - (100.0 - target_percentile));

    const double adjusted_percentile =
        std::max(percentile_delta, inv_percentile_delta) / 100.0;

    stop_profit =
        this->open_order_ptr->day_candle.range() * adjusted_percentile;
  }

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
