#ifndef OANDA__TAO_BOT_is_spiking
#define OANDA__TAO_BOT_is_spiking

#include "is_range_min_height.cpp" // is_range_min_height
#include "spike_score.cpp"         // spike_score
#include "tao_bot.h"               // Oanda::TaoBot

bool Oanda::TaoBot::is_spiking() {
  if (!this->spike_candles.current.open || !this->spike_candles.previous.open) {
    return false;
  }

  if (!is_range_min_height()) {
    return false;
  }

  const double spike_score_ = spike_score(this->spike_candles);

  if (spike_score_ < this->SPIKE_ENTRY_SCORE) {
    return false;
  }

  return this->spike_candles.current.range() >=
         this->SPIKE_HEIGHT_RATIO * this->day_candle.range();
}

#endif
