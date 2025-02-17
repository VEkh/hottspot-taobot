#ifndef ALPACA__TAO_BOT_should_reverse_profit
#define ALPACA__TAO_BOT_should_reverse_profit

#include "first_reversal_after.cpp"   // first_reversal_after
#include "is_trend_slipping.cpp"      // is_trend_slipping
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal_after.cpp"  // latest_reversal_after
#include "tao_bot.h"                  // Alpaca::TaoBot, reversal_t
#include <string>                     // std::string

bool Alpaca::TaoBot::should_reverse_profit() {
  if (this->closed_positions.empty()) {
    return false;
  }

  reversal_t stop_profit_reversal = latest_reversal_after(
      this->reversals, this->open_order_ptr->timestamp,
      this->open_order_ptr->entry_reversal.opposite_type());

  if (stop_profit_reversal.at) {
    const reversal_t record_reversal =
        latest_record_reversal(stop_profit_reversal.type);

    stop_profit_reversal =
        first_reversal_after(this->reversals, this->open_order_ptr->timestamp,
                             stop_profit_reversal.type, record_reversal.mid);

    if (record_reversal.mid == stop_profit_reversal.mid &&
        is_trend_slipping(this->open_order_ptr, this->EQUATOR_PERCENTILE)) {
      this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

      return true;
    }
  }

  return false;
}

#endif
