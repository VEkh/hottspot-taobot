#ifndef ALPACA__TAO_BOT_should_read_candles
#define ALPACA__TAO_BOT_should_read_candles

#include "db/candle/candle.cpp" // DB::Candle
#include "tao_bot.h"            // Alpaca::TaoBot, candle_bounds_t, candle_t

bool Alpaca::TaoBot::should_read_candles() {
  const candle_bounds_t current_epoch_bounds = DB::Candle::timestamp_to_bounds(
      this->db_candle.duration_minutes, this->current_epoch);

  if (current_epoch_bounds.opened_at <=
      this->market_availability.market_epochs.open) {
    return false;
  }

  if (this->latest_candles.empty()) {
    return true;
  }

  const candle_t latest_candle = this->latest_candles.back();

  return current_epoch_bounds.opened_at != latest_candle.closed_at;
}

#endif
