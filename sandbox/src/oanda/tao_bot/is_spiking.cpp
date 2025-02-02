#ifndef OANDA__TAO_BOT_is_spiking
#define OANDA__TAO_BOT_is_spiking

#include "spike_score.cpp" // spike_score
#include "tao_bot.h"       // Oanda::TaoBot

bool Oanda::TaoBot::is_spiking() {
  if (!this->spike_candles.current.open || !this->spike_candles.previous.open) {
    return false;
  }

  // TODO: Decide
  if (this->day_candle.range_open_percent() <
      this->api_client.config.spike_min_price_action) {
    return false;
  }

  const double spike_score_ = spike_score(this->spike_candles);

  // TODO: Decide
  // if (spike_score_ < this->SPIKE_ENTRY_SCORE) {
  if (spike_score_ < this->api_client.config.spike_entry_score) {
    return false;
  }

  return this->spike_candles.current.range() >=
         this->api_client.config.spike_height_ratio * this->day_candle.range();

  // return this->spike_candles.current.range() >=
  //        this->SPIKE_HEIGHT_RATIO * this->day_candle.range();
}

#endif
