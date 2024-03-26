// TODO: Decide
#ifndef ALPACA__TAO_BOT_set_reversals_timeframe_minutes
#define ALPACA__TAO_BOT_set_reversals_timeframe_minutes

#include "is_trending.cpp" // is_trending
#include "tao_bot.h"       // Alpaca::TaoBot, reversals_t
#include <algorithm>       // std::max
#include <string>          // std::string

void Alpaca::TaoBot::set_reversals_timeframe_minutes(reversals_t &source,
                                                     reversals_t &target) {
  if (!this->api_client.config.is_secondary_reversal_timeframe_dynamic) {
    return;
  }

  if (!is_trending()) {
    return;
  }

  if (this->closed_positions.empty()) {
    return;
  }

  const position_t last_position = this->closed_positions.back();

  const order_action_t order_action = last_position.open_order.action;

  const std::string key =
      order_action == order_action_t::BUY ? "lows" : "highs";

  const int default_timeframe_minutes =
      this->api_client.config.secondary_reversal_timeframe_minutes;

  const int source_timeframe_minutes =
      source.avg_record_delta_seconds[key] / 60.0;

  const int timeframe_minutes =
      std::max(source_timeframe_minutes, default_timeframe_minutes);

  target.timeframe_minutes = timeframe_minutes;
}

#endif
