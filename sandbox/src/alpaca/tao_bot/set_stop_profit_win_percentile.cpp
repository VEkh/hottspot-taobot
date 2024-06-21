// TODO: Decide
#ifndef ALPACA__TAO_BOT_set_stop_profit_win_percentile
#define ALPACA__TAO_BOT_set_stop_profit_win_percentile

#include "is_short_order_duration.cpp" // is_short_order_duration // TODO: Decide
#include "max_profit_day_range_percent.cpp" // max_profit_day_range_percent
#include "tao_bot.h"                        // Alpaca:: TaoBot
#include <map>                              // std::map

void Alpaca::TaoBot::set_stop_profit_win_percentile() {
  if (!this->open_order_ptr) {
    return;
  }

  if (!is_short_order_duration(this->open_order_ptr)) {
    return;
  }

  std::map<double, int> tiers =
      this->api_client.config.stop_profit_percentile_tiers;

  if (tiers.empty()) {
    this->win_percentile = this->api_client.config.win_percentile;

    return;
  }

  const double max_profit_day_range_percent_ =
      max_profit_day_range_percent(this->open_order_ptr);

  std::map<double, int>::iterator it;

  for (it = tiers.begin(); it != tiers.end(); it++) {
    if (max_profit_day_range_percent_ >= it->first) {
      this->win_percentile = it->second;
    }
  }
}

#endif
