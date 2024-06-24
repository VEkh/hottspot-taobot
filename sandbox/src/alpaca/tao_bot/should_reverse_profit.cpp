#ifndef ALPACA__TAO_BOT_should_reverse_profit
#define ALPACA__TAO_BOT_should_reverse_profit

#include "first_reversal_after.cpp"   // first_reversal_after
#include "is_in_win_percentile.cpp"   // is_in_win_percentile
#include "is_trend_slipping.cpp"      // is_trend_slipping
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal_after.cpp"  // latest_reversal_after
#include "tao_bot.h"                  // Alpaca::TaoBot, reversal_t
#include <string>                     // std::string

bool Alpaca::TaoBot::should_reverse_profit() {
  const std::string config = this->api_client.config.reverse_profit_during;

  if (config.empty()) {
    return false;
  }

  reversal_t stop_profit_reversal = latest_reversal_after(
      this->secondary_reversals, this->open_order_ptr->timestamp,
      this->open_order_ptr->entry_reversal.opposite_type());

  if (stop_profit_reversal.at) {
    bool should_close = false;

    if (!this->closed_positions.empty()) {
      if (config == "RECORD_AFTER_INIT_AND_SLIP") {
        const reversal_t record_reversal =
            latest_record_reversal(this->reversals, stop_profit_reversal.type);

        stop_profit_reversal = first_reversal_after(
            this->secondary_reversals, this->open_order_ptr->timestamp,
            stop_profit_reversal.type, true);

        if (record_reversal.mid == stop_profit_reversal.mid &&
            is_trend_slipping(this->open_order_ptr)) {
          should_close = true;
        }
      }

      // TODO: Decide
      if (config == "WIN_PERCENTILE_AFTER_INIT_AND_SLIP" &&
          is_in_win_percentile(this->open_order_ptr,
                               this->open_order_ptr->max_profit) &&
          is_trend_slipping(this->open_order_ptr)) {
        should_close = true;
      }
    }

    if (should_close) {
      this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

      return true;
    }
  }

  return false;
}

#endif
