#ifndef ALPACA__TAO_BOT_should_reverse_profit
#define ALPACA__TAO_BOT_should_reverse_profit

#include "is_trend_slipping.cpp"            // is_trend_slipping
#include "latest_record_reversal_after.cpp" // latest_record_reversal_after
#include "tao_bot.h"                        // Alpaca::TaoBot, reversal_t

bool Alpaca::TaoBot::should_reverse_profit() {
  if (!this->api_client.config.should_await_record_break &&
      this->closed_positions.empty()) {
    return false;
  }

  // TODO: Make the timestamp the max_profit_at
  reversal_t stop_profit_reversal = latest_record_reversal_after(
      this->reversals, this->open_order_ptr->timestamp,
      this->open_order_ptr->entry_reversal.opposite_type());

  // reversal_t stop_profit_reversal = latest_record_reversal_after(
  //     this->reversals, this->open_order_ptr->timestamp,
  //     this->open_order_ptr->entry_reversal.opposite_type());

  double trends_slip_percentile = this->EQUATOR_PERCENTILE;

  if (stop_profit_reversal.at &&
      is_trend_slipping(this->open_order_ptr, trends_slip_percentile)) {
    this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

    return true;
  }

  return false;
}

#endif
