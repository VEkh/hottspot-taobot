#ifndef ALPACA__TAO_BOT_are_latest_records_epoch_same
#define ALPACA__TAO_BOT_are_latest_records_epoch_same

#include "latest_record_reversal.cpp" // latest_record_reversal
#include "tao_bot.h"                  // Alpaca::TaoBot, reversals_t

bool Alpaca::TaoBot::are_latest_records_epoch_same(reversals_t &reversals_) {
  const reversal_t latest_high = latest_record_reversal(reversals_, "high");
  const reversal_t latest_low = latest_record_reversal(reversals_, "low");

  return latest_high.at == latest_low.at;
}

#endif
