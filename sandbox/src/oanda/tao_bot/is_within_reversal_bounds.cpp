// TODO: Decide
#ifndef OANDA__TAO_BOT_is_within_reversal_bounds
#define OANDA__TAO_BOT_is_within_reversal_bounds

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Oanda::TaoBot, reversal

bool Oanda::TaoBot::is_within_reversal_bounds(const reversal_t &reversal) {
  const double mid = current_mid();

  if (reversal.type == reversal_type_t::REVERSAL_LOW) {
    return mid >= reversal.mid;
  }

  if (reversal.type == reversal_type_t::REVERSAL_HIGH) {
    return mid < reversal.mid;
  }

  return false;
}

#endif
