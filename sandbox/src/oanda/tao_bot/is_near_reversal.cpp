// TODO: Define
#ifndef OANDA__TAO_BOT_is_near_reversal
#define OANDA__TAO_BOT_is_near_reversal

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Oanda::TaoBot, reversal_t
#include <math.h>          // abs

bool Oanda::TaoBot::is_near_reversal(reversal_t &reversal) {
  const double reversal_proximity_ratio =
      this->api_client.config.reversal_proximity_ratio;

  if (!reversal_proximity_ratio) {
    return true;
  }

  if (!reversal.mid) {
    return false;
  }

  const double delta = abs(current_mid() - reversal.mid);
  const double threshold = reversal_proximity_ratio * this->day_candle.range();

  return delta <= threshold;
}

#endif
