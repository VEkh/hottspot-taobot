#ifndef ALPACA__TAO_BOT_latest_record_as_reversal
#define ALPACA__TAO_BOT_latest_record_as_reversal

#include "tao_bot.h" // Alpaca::TaoBot, reversal_t, reversal_type_t

Alpaca::TaoBot::reversal_t Alpaca::TaoBot::latest_record_as_reversal(
    const reversal_type_t type = reversal_type_t::REVERSAL_NULL) {
  reversal_t record_high = {
      .at = this->day_candle.high_at,
      .is_record = true,
      .is_running_record = true,
      .mid = this->day_candle.high,
      .timeframe_minutes = 1,
      .type = reversal_type_t::REVERSAL_HIGH,
  };

  reversal_t record_low = {
      .at = this->day_candle.low_at,
      .is_record = true,
      .is_running_record = true,
      .mid = this->day_candle.low,
      .timeframe_minutes = 1,
      .type = reversal_type_t::REVERSAL_LOW,
  };

  if (type == reversal_type_t::REVERSAL_HIGH) {
    return record_high;
  }

  if (type == reversal_type_t::REVERSAL_LOW) {
    return record_low;
  }

  if (record_high.at > record_low.at) {
    return record_high;
  }

  return record_low;
}

#endif
