// TODO: Decide
#ifndef ALPACA__TAO_BOT_build_reversals
#define ALPACA__TAO_BOT_build_reversals

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Alpaca::TaoBot
#include <math.h>          // INFINITY

void Alpaca::TaoBot::build_reversals() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  const double mid = current_mid();
  const int reversal_timeframe_seconds =
      this->api_client.config.reversal_timeframe_minutes * 60;

  if (mid > this->reversals.pending_high) {
    this->reversals.pending_high_at = this->current_epoch;
    this->reversals.pending_high = mid;
  }

  if (this->current_epoch - this->reversals.pending_high_at >=
      reversal_timeframe_seconds) {
    bool should_append;

    if (this->reversals.highs.empty()) {
      should_append = true;
    } else {
      const reversal_t last_high = this->reversals.highs.back();
      should_append = last_high.mid != this->reversals.pending_high &&
                      this->reversals.pending_high_at - last_high.at >=
                          reversal_timeframe_seconds;
    }

    if (should_append) {
      this->reversals.highs.push_back({
          .at = this->reversals.pending_high_at,
          .mid = this->reversals.pending_high,
      });

      this->reversals.pending_high_at = this->current_epoch;
      this->reversals.pending_high = -INFINITY;
    }
  }

  if (mid < this->reversals.pending_low) {
    this->reversals.pending_low_at = this->current_epoch;
    this->reversals.pending_low = mid;
  }

  if (this->current_epoch - this->reversals.pending_low_at >=
      reversal_timeframe_seconds) {
    bool should_append;

    if (this->reversals.lows.empty()) {
      should_append = true;
    } else {
      const reversal_t last_low = this->reversals.lows.back();
      should_append = last_low.mid != this->reversals.pending_low &&
                      this->reversals.pending_low_at - last_low.at >=
                          reversal_timeframe_seconds;
    }

    if (should_append) {
      this->reversals.lows.push_back({
          .at = this->reversals.pending_low_at,
          .mid = this->reversals.pending_low,
      });

      this->reversals.pending_low_at = this->current_epoch;
      this->reversals.pending_low = INFINITY;
    }
  }
}

#endif
