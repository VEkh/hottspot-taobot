// TODO: Decide
#ifndef ALPACA__CLIENT_is_reversal_near_peak
#define ALPACA__CLIENT_is_reversal_near_peak

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h"                // Alpaca::TaoBot, reversal_t

bool Alpaca::TaoBot::is_reversal_near_peak(const reversal_t reversal) {
  const double reversal_mid_percentile = day_range_percentile(reversal.mid);
  const double entry_percentile =
      this->api_client.config.trend_entry_percentile;

  if (reversal.type == reversal_type_t::REVERSAL_LOW) {
    return reversal_mid_percentile >= 100.0 - entry_percentile;
  }

  return reversal_mid_percentile <= entry_percentile;
}

#endif
