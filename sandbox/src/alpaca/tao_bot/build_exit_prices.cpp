#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "is_non_init_reversing.cpp" // is_non_init_reversing // TODO: Decide
#include "tao_bot.h"                 // Alpaca::TaoBot
#include <algorithm>                 // std::max // TODO: Decide
#include <math.h>                    // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double execution_mid = this->open_order_ptr->execution_price;
  const double peak_padding_cents = 0.02;
  const order_action_t action = this->open_order_ptr->action;

  const double reversal_delta = action == order_action_t::BUY
                                    ? entry_reversal_mid - execution_mid
                                    : execution_mid - entry_reversal_mid;

  double stop_loss = reversal_delta ? reversal_delta : peak_padding_cents;
  double stop_profit = 0.0;

  // TODO: Decide
  // if (is_non_init_reversing(this->open_order_ptr)) {
  //   const double day_range = this->day_candle.range();

  //   if (this->api_client.config.non_init_reversing_stop_loss_ratio) {
  //     const double truncated_stop_loss =
  //         this->api_client.config.non_init_reversing_stop_loss_ratio *
  //         day_range;

  //     stop_loss = std::max(truncated_stop_loss, stop_loss);
  //   }

  //   if (this->api_client.config.non_init_reversing_trailing_stop_loss_ratio)
  //   {
  //     const double truncated_stop_loss =
  //         this->api_client.config.non_init_reversing_trailing_stop_loss_ratio
  //         *
  //             day_range +
  //         this->open_order_ptr->max_profit;

  //     stop_loss = std::max(truncated_stop_loss, stop_loss);
  //   }
  // }

  // TODO: Decide
  if (!this->closed_positions.empty() &&
      this->api_client.config.peak_padding_ratio) {
    stop_loss -=
        this->api_client.config.peak_padding_ratio * this->day_candle.range();
  } else {
    stop_loss -= peak_padding_cents;
  }

  // TODO: Decide
  if (this->should_stop_profit) {
    const double stop_profit_reversal_mid =
        this->open_order_ptr->stop_profit_reversal.mid;

    stop_profit = action == order_action_t::BUY
                      ? stop_profit_reversal_mid - execution_mid
                      : execution_mid - stop_profit_reversal_mid;
  }

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
