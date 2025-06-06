#ifndef OANDA__TAO_BOT_build_spike_candles
#define OANDA__TAO_BOT_build_spike_candles

#include "current_mid.cpp"      // current_mid
#include "db/candle/candle.cpp" // DB::Candle
#include "tao_bot.h"            // Oanda::TaoBot, candle_t
#include <algorithm>            // std::max, std::min

void Oanda::TaoBot::build_spike_candles() {
  if (this->open_order_ptr) {
    return;
  }

  // TODO: Decide
  if (!this->api_client.config.should_enter_at_spike) {
    return;
  }

  const candle_bounds_t bounds = DB::Candle::timestamp_to_bounds(
      this->SPIKE_DURATION_MINUTES, this->current_epoch);

  if (this->spike_candles.current.opened_at &&
      bounds.opened_at != this->spike_candles.current.opened_at) {
    this->spike_candles.day = this->day_candle;
    this->spike_candles.penultimate = this->spike_candles.previous;
    this->spike_candles.previous = this->spike_candles.current;
    this->spike_candles.current = candle_t();
  }

  const double mid = current_mid();

  this->spike_candles.current.closed_at = bounds.closed_at;
  this->spike_candles.current.opened_at = bounds.opened_at;

  this->spike_candles.current.close = mid;

  this->spike_candles.current.open =
      this->spike_candles.current.open ? this->spike_candles.current.open : mid;

  this->spike_candles.current.high =
      std::max(mid, this->spike_candles.current.high);

  if (this->spike_candles.current.high == mid) {
    this->spike_candles.current.high_at == this->current_epoch;
  }

  this->spike_candles.current.low =
      std::min(mid, this->spike_candles.current.low);

  if (this->spike_candles.current.low == mid) {
    this->spike_candles.current.low_at == this->current_epoch;
  }
}

#endif
