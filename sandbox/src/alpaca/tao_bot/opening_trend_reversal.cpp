// TODO: Decide
#ifndef ALPACA__CLIENT_opening_trend_reversal
#define ALPACA__CLIENT_opening_trend_reversal

#include "current_mid.cpp"            // current_mid
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "tao_bot.h"                  // Alpaca::TaoBot, reversal_t

Alpaca::TaoBot::reversal_t Alpaca::TaoBot::opening_trend_reversal() {
  // const int await_minutes =
  // this->api_client.config.opening_trend_await_minutes;
  const int await_minutes = 0;

  if (!await_minutes) {
    return reversal_t();
  }

  if (this->current_epoch < this->market_open_epoch + await_minutes * 60) {
    return reversal_t();
  }

  const reversal_t record_high =
      latest_record_reversal(this->reversals, reversal_type_t::REVERSAL_HIGH);

  const reversal_t record_low =
      latest_record_reversal(this->reversals, reversal_type_t::REVERSAL_LOW);

  if (!record_low.mid) {
    return record_high;
  }

  if (!record_high.mid) {
    return record_low;
  }

  const double mid = current_mid();
  const double high_delta = abs(record_high.mid - mid);
  const double low_delta = abs(record_low.mid - mid);

  return low_delta >= high_delta ? record_low : record_high;
}

#endif
