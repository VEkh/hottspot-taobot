#ifndef ALPACA__TAO_BOT_max_profit_target_icon
#define ALPACA__TAO_BOT_max_profit_target_icon

#include "max_profit_day_range_percent.cpp" // max_profit_day_range_percent
#include "tao_bot.h"                        // Alpaca::TaoBot, order_t
#include <map>                              // std::map
#include <string>                           // std::string

std::string Alpaca::TaoBot::max_profit_target_icon(const order_t *order) {
  std::map<double, int> tiers = this->api_client.config.stop_profit_tiers;
  std::string out = "";

  if (!order) {
    return out;
  }

  if (tiers.empty()) {
    return out;
  }

  std::map<double, int>::iterator it;
  const double max_profit_percent = max_profit_day_range_percent(order);

  out = " ";

  for (it = tiers.begin(); it != tiers.end(); it++) {
    if (it == tiers.begin()) {
      continue;
    }

    if (max_profit_percent >= it->first) {
      out += "🔥";
    }
  }

  return out;
}

#endif
