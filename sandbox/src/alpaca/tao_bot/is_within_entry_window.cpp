#ifndef ALPACA__TAO_BOT_is_within_entry_window
#define ALPACA__TAO_BOT_is_within_entry_window

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Alpaca::TaoBot, reversal_t, reversal_type_t
#include <math.h>          // abs

bool Alpaca::TaoBot::is_within_entry_window(const reversal_t reversal) {
  const double mid = current_mid();

  if (!reversal.at || !reversal.mid) {
    return false;
  }

  if (reversal.type == reversal_type_t::REVERSAL_HIGH && mid < reversal.mid) {
    return true;
  }

  if (reversal.type == reversal_type_t::REVERSAL_LOW && mid > reversal.mid) {
    return true;
  }

  return false;
}

#endif
