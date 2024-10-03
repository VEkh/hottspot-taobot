// TODO: Decide
#ifndef OANDA__TAO_BOT_should_stop_profit
#define OANDA__TAO_BOT_should_stop_profit

#include "latest_reversal_after.cpp" // latest_reversal_after
#include "tao_bot.h"                 // Oanda::TaoBot, reversal_t

bool Oanda::TaoBot::should_stop_profit() {
  if (!this->api_client.config.should_stop_profit) {
    return false;
  }

  if (!this->open_order_ptr) {
    return false;
  }

  reversals_t stop_profit_reversals =
      this->secondary_reversals.timeframe_minutes ? this->secondary_reversals
                                                  : this->reversals;

  reversal_t entry_reversal_ = this->open_order_ptr->entry_reversal;

  const reversal_t stop_profit_reversal = latest_reversal_after(
      stop_profit_reversals, this->open_order_ptr->timestamp,
      entry_reversal_.opposite_type());

  if (!stop_profit_reversal.at) {
    return false;
  }

  const double execution_mid = this->open_order_ptr->execution_price;

  const double stop_profit_reversal_profit =
      stop_profit_reversal.type == reversal_type_t::REVERSAL_HIGH
          ? stop_profit_reversal.mid - execution_mid
          : execution_mid - stop_profit_reversal.mid;

  const double current_profit = this->open_order_ptr->profit;
  const double stop_profit_ratio = this->api_client.config.stop_profit_ratio;

  if (stop_profit_reversal_profit > 0 &&
      current_profit >= stop_profit_ratio * stop_profit_reversal_profit) {
    return true;
  }

  return false;
}

#endif
