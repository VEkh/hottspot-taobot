// TODO: Decide
#ifndef ALPACA__TAO_BOT_set_stop_profit_reversals_timeframe
#define ALPACA__TAO_BOT_set_stop_profit_reversals_timeframe

#include "is_short_order_duration.cpp" // is_short_order_duration // TODO: Decide
#include "max_profit_day_range_percent.cpp" // max_profit_day_range_percent
#include "tao_bot.h"                        // Alpaca:: TaoBot
#include <map>                              // std::map

void Alpaca::TaoBot::set_stop_profit_reversals_timeframe() {
  if (!this->open_order_ptr) {
    return;
  }

  if (!is_short_order_duration(this->open_order_ptr)) {
    return;
  }

  std::map<double, int> tiers = this->api_client.config.stop_profit_tiers;

  if (tiers.empty()) {
    return;
  }

  const double max_profit_day_range_percent_ =
      max_profit_day_range_percent(this->open_order_ptr);

  std::map<double, int>::iterator it;

  for (it = tiers.begin(); it != tiers.end(); it++) {
    if (max_profit_day_range_percent_ >= it->first) {
      this->tertiary_reversals.timeframe_minutes = it->second;
    }
  }
}

#endif
