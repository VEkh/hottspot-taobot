#ifndef OANDA__TAO_BOT_is_entry_signal_present
#define OANDA__TAO_BOT_is_entry_signal_present

#include "day_range_percentile.cpp"   // day_range_percentile
#include "first_reversal_after.cpp"   // first_reversal_after
#include "is_trending.cpp"            // is_trending
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "nearer_reversal.cpp"        // nearer_reversal
#include "tao_bot.h" // Oanda::TaoBot, position_t, reversal_t, reversal_type_t

// TODO: Decide
#include "is_within_reversal_bounds.cpp" // is_within_reversal_bounds
#include "latest_reversal_after.cpp"     // latest_reversal_after

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

      // TODO: Decide
      // if (last_position.close_order.stop_profit_reversal.at &&
      //     last_position.close_order.stop_profit_reversal.is_record) {
      //   did_last_position_stop_profit = true;
      // }

      did_last_position_stop_profit =
          (bool)last_position.close_order.stop_profit_reversal.at;
    }

    if (did_last_position_stop_profit) {
      const position_t last_position = this->closed_positions.back();

      reversal = last_position.close_order.stop_profit_reversal;
    } else {
      reversal_t first_high =
          first_reversal_after(this->reversals, this->current_trend.at,
                               reversal_type_t::REVERSAL_HIGH);

      reversal_t first_low =
          first_reversal_after(this->reversals, this->current_trend.at,
                               reversal_type_t::REVERSAL_LOW);
      if (!first_high.mid) {
        first_high = reversal_t();
      }

      if (!first_low.mid) {
        first_low = reversal_t();
      }

      if (first_high.mid &&
          day_range_percentile(this->day_candle, first_high.mid) <
              this->EQUATOR_PERCENTILE) {
        first_high = reversal_t();
      }

      if (first_low.mid &&
          day_range_percentile(this->day_candle, first_low.mid) >
              this->EQUATOR_PERCENTILE) {
        first_low = reversal_t();
      }

      reversal = nearer_reversal(first_high, first_low, current_mid());

      // TODO: Decide
      reversal.is_record_only_reversible = false;
      reversal.is_reversible = true;

      // TODO: Decide
      if (!is_within_reversal_bounds(reversal)) {
        reversal = reversal_t();
      }
    }

    const bool is_after_entry_epoch =
        this->current_epoch >=
        this->current_trend.at + this->spike_candles.current.duration_seconds();

    if (this->api_client.config.should_await_spike &&
        this->api_client.config.should_enter_at_spike &&
        this->current_trend.is_initialized && is_after_entry_epoch) {
      reversal.at = this->spike_candles.previous.opened_at;
      reversal.is_record_only_reversible = false;
      reversal.is_reversible = true;

      if (this->spike_candles.previous.trend() == trend_t::TREND_DOWN) {
        reversal.mid = this->spike_candles.previous.high;
        reversal.type = reversal_type_t::REVERSAL_HIGH;
      } else if (this->spike_candles.previous.trend() == trend_t::TREND_UP) {
        reversal.mid = this->spike_candles.previous.low;
        reversal.type = reversal_type_t::REVERSAL_LOW;
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
