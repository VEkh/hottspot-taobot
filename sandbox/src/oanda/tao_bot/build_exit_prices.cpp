#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h"                // Oanda::TaoBot
#include <algorithm>                // std::max
#include <math.h>                   // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double entry_reversal_mid = this->open_order_ptr->entry_reversal.mid;
  const double execution_price = this->open_order_ptr->execution_price;
  const order_action_t action = this->open_order_ptr->action;

  const double reversal_delta = abs(entry_reversal_mid - execution_price);

  const double stop_loss =
      -std::max(0.00001, reversal_delta) -
      this->STOP_LOSS_PADDING_RATIO * this->day_candle.range();

  const double execution_price_percentile =
      day_range_percentile(this->open_order_ptr->day_candle, execution_price);

  const double inv_execution_price_percentile =
      abs(100.0 - execution_price_percentile);

  const double max_percentile_delta =
      std::max(execution_price_percentile, inv_execution_price_percentile) /
      100.0;

  const double stop_profit =
      this->open_order_ptr->day_candle.range() * max_percentile_delta;

  return {
      .stop_loss = stop_loss,
      .stop_profit = stop_profit,
  };
}

#endif
