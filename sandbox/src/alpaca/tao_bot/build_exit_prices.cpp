#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max, std::min // TODO: Decide
#include <math.h>    // abs

// TODO: Decide
#include "day_range_percentile.cpp"     // day_range_percentile
#include "update_inverted_reversal.cpp" // update_inverted_reversal

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  update_inverted_reversal(this->open_order_ptr); // TODO: Decide

  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double execution_price = this->open_order_ptr->execution_price;
  const order_action_t action = this->open_order_ptr->action;

  // TODO: Decide
  // const double reversal_delta = action == order_action_t::BUY
  //                                   ? entry_reversal_mid - execution_price
  //                                   : execution_price - entry_reversal_mid;

  const double reversal_delta = -abs(entry_reversal_mid - execution_price);

  const double stop_loss = std::min(-0.01, reversal_delta) -
                           this->api_client.config.stop_loss_padding_ratio *
                               this->day_candle.range();

  double stop_profit = 0.0;

  // TODO: Decide
  if (this->api_client.config.should_stop_profit) {
    const double execution_price_percentile =
        day_range_percentile(this->open_order_ptr->day_candle, execution_price);

    const double inv_execution_price_percentile =
        abs(100.0 - execution_price_percentile);

    const double max_percentile_delta =
        std::max(execution_price_percentile, inv_execution_price_percentile) /
        100.0;

    // TODO: Decide
    stop_profit = this->api_client.config.stop_profit_multiplier *
                  this->open_order_ptr->day_candle.range() *
                  max_percentile_delta;
  }

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
