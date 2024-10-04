#ifndef OANDA__TAO_BOT_latest_reversal_after
#define OANDA__TAO_BOT_latest_reversal_after

#include "latest_reversal.cpp" // latest_reversal
#include "tao_bot.h" // Oanda::TaoBot,  reversal_t, reversals_t, reversal_type_t

Oanda::TaoBot::reversal_t Oanda::TaoBot::latest_reversal_after(
    reversals_t &reversals_, const double ref_epoch,
    const reversal_type_t reversal_type = reversal_type_t::REVERSAL_NULL) {
  if (!ref_epoch) {
    return reversal_t();
  }

  if (!reversals_.timeframe_minutes) {
    return reversal_t();
  }

  const reversal_t latest_reversal_ =
      latest_reversal(reversals_, reversal_type);

  const int reversal_minute = latest_reversal_.at / 60;
  const int ref_epoch_minute = ref_epoch / 60;

  return reversal_minute >= ref_epoch_minute ? latest_reversal_ : reversal_t();
}

#endif
