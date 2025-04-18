#ifndef ALPACA__TAO_BOT_latest_record_reversal
#define ALPACA__TAO_BOT_latest_record_reversal

#include "latest_record_as_reversal.cpp" // latest_record_as_reversal
#include "latest_reversal.cpp"           // latest_reversal
#include "tao_bot.h" // Alpaca::TaoBot, reversal_t, reversal_type_t

Alpaca::TaoBot::reversal_t Alpaca::TaoBot::latest_record_reversal(
    reversals_t &reversals_,
    const reversal_type_t type = reversal_type_t::REVERSAL_NULL) {
  const reversal_t reversal = latest_reversal(reversals_, type, true);
  const reversal_t record = latest_record_as_reversal(type);

  return reversal.mid == record.mid ? reversal : reversal_t();
}

#endif
