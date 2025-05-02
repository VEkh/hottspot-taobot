// TODO: Decide
#ifndef OANDA__TAO_BOT_should_reverse_profit
#define OANDA__TAO_BOT_should_reverse_profit

#include "is_trend_slipping.cpp"            // is_trend_slipping
#include "latest_record_reversal_after.cpp" // latest_record_reversal_after
#include "tao_bot.h"                        // Oanda::TaoBot, reversal_t

bool Oanda::TaoBot::should_reverse_profit() {
  if (this->api_client.config.should_enter_at_spike) {
    return false;
  }

  if (!this->api_client.config.should_always_reverse_profit &&
      this->closed_positions.empty()) {
    return false;
  }

  reversal_t stop_profit_reversal = latest_record_reversal_after(
      this->reversals, this->open_order_ptr->timestamp,
      this->open_order_ptr->entry_reversal.opposite_type());

  if (stop_profit_reversal.at &&
      is_trend_slipping(this->open_order_ptr, this->EQUATOR_PERCENTILE)) {
    this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

    return true;
  }

  return false;
}

#endif
