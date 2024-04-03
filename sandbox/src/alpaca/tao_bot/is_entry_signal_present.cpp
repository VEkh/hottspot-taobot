#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "has_reversal_been_used.cpp" // has_reversal_been_used
#include "is_trending.cpp"            // is_trending
#include "is_within_entry_window.cpp" // is_within_entry_window
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal.cpp"        // latest_reversal
#include "tao_bot.h"                  // Alpaca::TaoBot, position_t, reversal_t

bool Alpaca::TaoBot::is_entry_signal_present() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return false;
  }

  if (this->api_client.config.should_await_reversal_indicator) {
    if (this->reversals.any_empty()) {
      return false;
    }

    const bool is_trending_ = is_trending();

    reversal_t entry_reversal_ = latest_record_reversal(this->reversals);

    if (has_reversal_been_used(entry_reversal_)) {
      return false;
    }

    if (!is_trending_ && !is_within_entry_window(entry_reversal_)) {
      return false;
    }

    if (this->api_client.config.trend_trigger_type == "cis" && is_trending_ &&
        this->secondary_reversals.timeframe_minutes) {
      const std::string key =
          this->current_trend.trend == trend_t::TREND_DOWN ? "high" : "low";

      if (this->current_trend.trend == trend_t::TREND_UP &&
          this->secondary_reversals.lows.empty()) {
        return false;
      }

      if (this->current_trend.trend == trend_t::TREND_DOWN &&
          this->secondary_reversals.highs.empty()) {
        return false;
      }

      const reversal_t secondary_reversal =
          latest_reversal(this->secondary_reversals, key);

      if (secondary_reversal.at < entry_reversal_.at) {
        return false;
      }

      if (secondary_reversal.at < this->current_trend.at) {
        return false;
      }

      entry_reversal_ = secondary_reversal;
    }

    this->entry_reversal = entry_reversal_;

    return true;
  }

  return false;
}

#endif
