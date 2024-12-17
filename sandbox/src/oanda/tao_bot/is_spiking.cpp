// TODO: Decide
#ifndef OANDA__TAO_BOT_is_spiking
#define OANDA__TAO_BOT_is_spiking

#include "spike_score.cpp" // spike_score
#include "tao_bot.h"       // Oanda::TaoBot

bool Oanda::TaoBot::is_spiking() {
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
