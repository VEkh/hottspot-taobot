// TODO: Decide
#ifndef OANDA__TAO_BOT_is_warm_up_within_max_height
#define OANDA__TAO_BOT_is_warm_up_within_max_height

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::is_warm_up_within_max_height() {
  const double max_height_ratio = this->api_client.config.warm_up_max_height;

  if (!max_height_ratio) {
    return true;
  }

  return this->day_candle.range_open_percent() <= max_height_ratio * 100.0;
}

#endif
