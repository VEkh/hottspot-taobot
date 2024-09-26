// TODO: Define
#ifndef OANDA__TAO_BOT_is_near_reversal
#define OANDA__TAO_BOT_is_near_reversal

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Oanda::TaoBot, reversal_t
#include <math.h>          // abs

bool Oanda::TaoBot::is_near_reversal(const reversal_t &reversal) {
  if (!this->api_client.config.should_enter_near_reversal) {
    return true;
  }

  if (!reversal.mid) {
    return false;
  }

  const double delta = abs(current_mid() - reversal.mid);
  const double threshold = 0.01 * this->day_candle.range();

  return delta <= threshold;
}

#endif
