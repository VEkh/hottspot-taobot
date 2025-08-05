#ifndef OANDA__TAO_BOT_is_range_min_height
#define OANDA__TAO_BOT_is_range_min_height

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::is_range_min_height() {
  if (!this->api_client.config.should_enter_at_spike) {
    return true;
  }

  return this->day_candle.range_open_percent() >= 0.5;
}

#endif
