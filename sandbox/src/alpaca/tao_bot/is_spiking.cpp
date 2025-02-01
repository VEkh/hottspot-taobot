// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_spiking
#define ALPACA__TAO_BOT_is_spiking

#include "spike_score.cpp" // spike_score
#include "tao_bot.h"       // Alpaca::TaoBot

bool Alpaca::TaoBot::is_spiking() {
  if (!this->spike_candles.current.open || !this->spike_candles.previous.open) {
    return false;
  }

  if (this->day_candle.range_open_percent() < 0.5) {
    return false;
  }

  const double spike_score_ = spike_score(this->spike_candles);

  if (spike_score_ < this->api_client.config.spike_entry_score) {
    return false;
  }

  return this->spike_candles.current.range() >=
         this->api_client.config.spike_height_ratio * this->day_candle.range();
}

#endif
