// TODO: Decide
#ifndef ALPACA__TAO_BOT_latest_record_reversal_after
#define ALPACA__TAO_BOT_latest_record_reversal_after

#include "is_reversal_after.cpp"      // is_reversal_after
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "tao_bot.h" // Alpaca::TaoBot,  reversal_t, reversals_t, reversal_type_t

Alpaca::TaoBot::reversal_t Alpaca::TaoBot::latest_record_reversal_after(
    reversals_t &reversals_, const double ref_epoch,
    const reversal_type_t reversal_type = reversal_type_t::REVERSAL_NULL) {
  if (!ref_epoch) {
    return reversal_t();
  }

  if (!reversals_.timeframe_minutes) {
    return reversal_t();
  }

  const reversal_t latest_reversal_ =
      latest_record_reversal(reversals_, reversal_type);

  return is_reversal_after(latest_reversal_, ref_epoch) ? latest_reversal_
                                                        : reversal_t();
}

#endif
