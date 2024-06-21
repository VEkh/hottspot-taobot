#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "has_reversal_been_used.cpp" // has_reversal_been_used
#include "is_trending.cpp"            // is_trending
#include "is_within_entry_window.cpp" // is_within_entry_window
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal.cpp"        // latest_reversal
#include "tao_bot.h" // Alpaca::TaoBot, reversal_t, reversal_type_t

// TODO: Decide
#include "day_range_percentile.cpp"  // day_range_percentile
#include "first_reversal_after.cpp"  // first_reversal_after
#include "is_reversal_near_peak.cpp" // is_reversal_near_peak

bool Alpaca::TaoBot::is_entry_signal_present() {
  if (this->reversals.any_empty()) {
    return false;
  }

  const bool is_trending_ = is_trending();

  reversal_t entry_reversal_ = latest_record_reversal(this->reversals);

  // TODO: Decide
  if ((this->should_stop_profit || !this->dynamic_trend_type.empty()) &&
      !is_trending_ && !this->closed_positions.empty()) {
    const position_t last_position = this->closed_positions.back();

    const reversal_type_t type =
        last_position.open_order.action == order_action_t::BUY
            ? reversal_type_t::REVERSAL_HIGH
            : reversal_type_t::REVERSAL_LOW;

    entry_reversal_ = latest_record_reversal(this->reversals, type);
  }

  // TODO: Decide
  // if (this->should_stop_profit && !is_trending_ &&
  //     !this->closed_positions.empty()) {
  //   const position_t last_position = this->closed_positions.back();

  //   if (last_position.close_order.min_profit >
  //       last_position.close_order.stop_loss) {
  //   const reversal_type_t type =
  //       last_position.open_order.action == order_action_t::BUY ?
  //       reversal_type_t::REVERSAL_HIGH : reversal_type_t::REVERSAL_LOW;
  //
  //     entry_reversal_ = latest_reversal(this->secondary_reversals, type);

  //     if (entry_reversal_.at < last_position.close_order.timestamp) {
  //       return false;
  //     }
  //   } else {
  //   const reversal_type_t type =
  //       last_position.open_order.action == order_action_t::BUY ?
  //       reversal_type_t::REVERSAL_HIGH : reversal_type_t::REVERSAL_LOW;

  //     entry_reversal_ = latest_record_reversal(this->reversals, type);
  //   }
  // }

  if (has_reversal_been_used(entry_reversal_)) {
    return false;
  }

  if (!is_trending_ && !is_within_entry_window(entry_reversal_)) {
    return false;
  }

  if (is_trending_ && this->secondary_reversals.timeframe_minutes &&
      this->api_client.config.second_reversal_ref_type.empty()) {
    const std::string dynamic_trend_type =
        this->api_client.config.dynamic_trend_type;
    reversal_t secondary_reversal;

    // TODO: Decide
    bool skip_checks = false;

    // TODO: Decide
    if (dynamic_trend_type == "FIRST_TRANS") {
      const reversal_t first_high = first_reversal_after(
          this->secondary_reversals, this->current_trend.at,
          reversal_type_t::REVERSAL_HIGH);

      const reversal_t first_low = first_reversal_after(
          this->secondary_reversals, this->current_trend.at,
          reversal_type_t::REVERSAL_LOW);

      if (first_high.mid && day_range_percentile(first_high.mid) >= 50) {
        secondary_reversal = first_high;
      } else if (first_low.mid && day_range_percentile(first_low.mid) <= 50) {
        secondary_reversal = first_low;
      }
    } else {
      const reversal_type_t trend_type =
          this->current_trend.trend == trend_t::TREND_DOWN
              ? reversal_type_t::REVERSAL_HIGH
              : reversal_type_t::REVERSAL_LOW;

      if (this->current_trend.trend == trend_t::TREND_UP &&
          this->secondary_reversals.lows.empty()) {
        return false;
      }

      if (this->current_trend.trend == trend_t::TREND_DOWN &&
          this->secondary_reversals.highs.empty()) {
        return false;
      }

      secondary_reversal = first_reversal_after(
          this->secondary_reversals, this->current_trend.at, trend_type);
    }

    // TODO: Decide
    if (!this->api_client.config.reverse_profit_during.empty() &&
        !this->closed_positions.empty()) {
      const position_t last_position = this->closed_positions.back();
      const bool should_await_config =
          this->api_client.config.should_await_after_no_max_loss;

      if (!should_await_config &&
          last_position.close_order.stop_profit_reversal.at) {
        secondary_reversal = last_position.close_order.stop_profit_reversal;
        skip_checks = true;
      }
    }

    if (!skip_checks) {
      // TODO: Decide
      if (this->api_client.config.should_trend_entry_await_correction &&
          secondary_reversal.at < entry_reversal_.at) {
        return false;
      }

      // TODO: Decide
      // if (this->api_client.config.trend_entry_percentile &&
      //     !is_reversal_near_peak(secondary_reversal)) {
      //   return false;
      // }

      // TODO: Decide
      // if (this->api_client.config.should_trend_enter_at_record) {
      //   const reversal_t latest_record =
      //       latest_record_reversal(this->reversals, trend_type);

      //   if (latest_record.mid != secondary_reversal.mid) {
      //     return false;
      //   }
      // }

      const int reversal_at_minute = secondary_reversal.at / 60;
      const int trend_at_minute = this->current_trend.at / 60;

      if (reversal_at_minute < trend_at_minute) {
        return false;
      }
    }

    entry_reversal_ = secondary_reversal;
  }

  // TODO: Decide
  // if (is_trending_ && this->secondary_reversals.timeframe_minutes &&
  //     !this->api_client.config.second_reversal_ref_type.empty()) {
  //   const std::string ref_type =
  //       this->api_client.config.second_reversal_ref_type;

  //   reversal_t ref_reversal;

  //   if (ref_type == "DYNAMIC") {
  //     const reversal_type_t reversal_type =
  //         this->current_trend.trend == trend_t::TREND_DOWN
  //             ? reversal_type_t::REVERSAL_HIGH
  //             : reversal_type_t::REVERSAL_LOW;

  //     ref_reversal = first_reversal_after(
  //         this->secondary_reversals, this->current_trend.at, reversal_type);
  //   } else if (this->api_client.config.second_reversal_ref_type == "FIRST") {
  //     ref_reversal = first_reversal_after(this->secondary_reversals,
  //                                         this->current_trend.at);
  //   }

  //   if (!ref_reversal.at) {
  //     return false;
  //   }

  //   const reversal_t secondary_reversal =
  //       first_reversal_after(this->secondary_reversals, ref_reversal.at);

  //   if (!secondary_reversal.at) {
  //     return false;
  //   }

  //   entry_reversal_ = secondary_reversal;
  // }

  this->entry_reversal = entry_reversal_;

  return true;
}

#endif
