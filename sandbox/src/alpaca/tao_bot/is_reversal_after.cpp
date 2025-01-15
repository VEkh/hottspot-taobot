#ifndef ALPACA__TAO_BOT_is_reversal_after
#define ALPACA__TAO_BOT_is_reversal_after

#include "tao_bot.h" // Alpaca::TaoBot, reversal_t

bool Alpaca::TaoBot::is_reversal_after(const reversal_t reversal,
                                       const double ref_epoch) {
  const int reversal_minute = reversal.at / 60;
  const int ref_epoch_minute = ref_epoch / 60;

  return reversal_minute >= ref_epoch_minute;
}

#endif
