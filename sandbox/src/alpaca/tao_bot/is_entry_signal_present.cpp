#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "day_range_percentile.cpp"   // day_range_percentile
#include "first_reversal_after.cpp"   // first_reversal_after
#include "is_trending.cpp"            // is_trending
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "tao_bot.h" // Alpaca::TaoBot, position_t, reversal_t, reversal_type_t

bool Alpaca::TaoBot::is_entry_signal_present() {
  const bool is_trending_ = is_trending();

  reversal_t entry_reversal_ = latest_record_reversal();

  if (!is_trending_ && !this->closed_positions.empty()) {
    const position_t last_position = this->closed_positions.back();

    const reversal_type_t type =
        last_position.open_order.action == order_action_t::BUY
            ? reversal_type_t::REVERSAL_HIGH
            : reversal_type_t::REVERSAL_LOW;

    entry_reversal_ = latest_record_reversal(type);
  }

  if (is_trending_ && this->reversals.timeframe_minutes) {
    reversal_t reversal;

    bool did_last_position_stop_profit = false;

    if (!this->closed_positions.empty()) {
      const position_t last_position = this->closed_positions.back();

      did_last_position_stop_profit =
          (bool)last_position.close_order.stop_profit_reversal.at;
    }

    if (did_last_position_stop_profit) {
      const position_t last_position = this->closed_positions.back();

      reversal = last_position.close_order.stop_profit_reversal;
    } else {
      const reversal_t first_high =
          first_reversal_after(this->reversals, this->current_trend.at,
                               reversal_type_t::REVERSAL_HIGH);

      const reversal_t first_low =
          first_reversal_after(this->reversals, this->current_trend.at,
                               reversal_type_t::REVERSAL_LOW);

      if (first_high.mid &&
          day_range_percentile(this->day_candle, first_high.mid) >=
              this->EQUATOR_PERCENTILE) {
        reversal = first_high;
      } else if (first_low.mid &&
                 day_range_percentile(this->day_candle, first_low.mid) <=
                     this->EQUATOR_PERCENTILE) {
        reversal = first_low;
      }

      const int reversal_at_minute = reversal.at / 60;
      const int trend_at_minute = this->current_trend.at / 60;

      if (reversal_at_minute < trend_at_minute) {
        reversal = reversal_t();
      }
    }

    entry_reversal_ = reversal;
  }

  if (entry_reversal_.at) {
    this->entry_reversal = entry_reversal_;

    return true;
  }

  return false;
}

#endif
