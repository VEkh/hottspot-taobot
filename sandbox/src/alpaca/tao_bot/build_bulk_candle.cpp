// TODO: Decide
#ifndef ALPACA__TAO_BOT_build_bulk_candle
#define ALPACA__TAO_BOT_build_bulk_candle

#include "tao_bot.h" // Alpaca::TaoBot, candle_t
#include <algorithm> // std::max, std::max

void Alpaca::TaoBot::build_bulk_candle() {
  const bool is_updated = floor(this->bulk_candle.closed_at / 60) ==
                          floor(this->current_epoch / 60);

  if (is_updated) {
    return;
  }

  this->bulk_candle = candle_t();

  const double candles_timeframe_minutes =
      this->api_client.config.candles_timeframe_minutes;

  const double start_epoch =
      candles_timeframe_minutes
          ? std::max(this->market_open_epoch,
                     this->current_epoch - candles_timeframe_minutes * 60)
          : this->market_open_epoch;

  for (const candle_t candle : this->latest_candles) {
    if (candle.opened_at < start_epoch) {
      continue;
    }

    const double mid = candle.close;

    this->bulk_candle.close = mid;
    this->bulk_candle.high = std::max(this->bulk_candle.high, mid);
    this->bulk_candle.low = std::min(this->bulk_candle.low, mid);
    this->bulk_candle.open =
        this->bulk_candle.open ? this->bulk_candle.open : candle.open;
  }

  this->bulk_candle.closed_at = this->current_epoch;
}

#endif
