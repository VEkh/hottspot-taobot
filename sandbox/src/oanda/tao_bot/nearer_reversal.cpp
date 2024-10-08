#ifndef OANDA__TAO_BOT_nearer_reversal
#define OANDA__TAO_BOT_nearer_reversal

#include "tao_bot.h" // Oanda::TaoBot, reversal_t
#include <math.h>    // abs

Oanda::TaoBot::reversal_t Oanda::TaoBot::nearer_reversal(const reversal_t a,
                                                         const reversal_t b,
                                                         const double ref_mid) {
  const double a_delta = abs(ref_mid - a.mid);
  const double b_delta = abs(ref_mid - b.mid);

  if (a.mid && a_delta <= b_delta) {
    return a;
  }

  if (b.mid && b_delta <= a_delta) {
    return b;
  }

  return reversal_t();
}

#endif
