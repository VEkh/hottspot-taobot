#ifndef OANDA__TAO_BOT_is_range_min_height
#define OANDA__TAO_BOT_is_range_min_height

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::is_range_min_height() {
  return this->day_candle.range_open_percent() >=
         this->api_client.config.range_min_height;
}

#endif
