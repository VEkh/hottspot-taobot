#ifndef OANDA__TAO_BOT_is_entry_signal_present
#define OANDA__TAO_BOT_is_entry_signal_present

#include "day_range_percentile.cpp"   // day_range_percentile
#include "first_reversal_after.cpp"   // first_reversal_after
#include "is_trending.cpp"            // is_trending
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "nearer_reversal.cpp"        // nearer_reversal
#include "tao_bot.h" // Oanda::TaoBot, position_t, reversal_t, reversal_type_t

// TODO: Decide
#include "is_near_reversal.cpp"      // is_near_reversal
#include "latest_reversal_after.cpp" // latest_reversal_after

bool Oanda::TaoBot::is_entry_signal_present() {
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
      // TODO: Decide
    } else if (!this->context_entry_reversal.mid) {
      reversal_t first_high =
          first_reversal_after(this->reversals, this->current_trend.at,
                               reversal_type_t::REVERSAL_HIGH);

      reversal_t first_low =
          first_reversal_after(this->reversals, this->current_trend.at,
                               reversal_type_t::REVERSAL_LOW);
      if (!first_high.mid) {
        first_high = reversal_t();
      }

      if (first_high.mid &&
          day_range_percentile(first_high.mid) < this->EQUATOR_PERCENTILE) {
        first_high = reversal_t();
      }

      if (!first_low.mid) {
        first_low = reversal_t();
      }

      if (first_low.mid &&
          day_range_percentile(first_low.mid) > this->EQUATOR_PERCENTILE) {
        first_low = reversal_t();
      }

      reversal = nearer_reversal(first_high, first_low, current_mid());

      // TODO: Decide
      if (!is_near_reversal(reversal)) {
        reversal = reversal_t();
      }

      // // TODO: Decide
      // if (reversal.mid) {
      //   this->context_entry_reversal = reversal;
      //   this->current_trend.at = this->current_epoch;
      //   this->current_trend.trend = reversal.to_trend_type();

      //   reversal = reversal_t();
      // }
      // TODO: Decide
    } else if (this->context_entry_reversal.mid) {
      reversal = latest_reversal_after(this->reversals, this->current_trend.at,
                                       this->context_entry_reversal.type);
    }

    entry_reversal_ = reversal;
  }

  if (entry_reversal_.at) {
    // TODO: Decide
    if (!this->is_entry_reversal) {
      entry_reversal_.type = entry_reversal_.opposite_type();
    }

    this->entry_reversal = entry_reversal_;

    return true;
  }

  return false;
}

#endif
