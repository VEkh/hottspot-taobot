// TODO: Decide
#ifndef ALPACA__TAO_BOT_set_trend_type
#define ALPACA__TAO_BOT_set_trend_type

#include "current_mid.cpp"          // current_mid
#include "day_range_percentile.cpp" // day_range_percentile
#include "is_trending.cpp"          // is_trending
#include "tao_bot.h"                // Alpaca::TaoBot, trend_t
#include <string>                   // std::string

void Alpaca::TaoBot::set_trend_type() {
  if (this->dynamic_trend_type.empty()) {
    return;
  }

  if (!is_trending()) {
    return;
  }

  if (this->open_order_ptr) {
    return;
  }

  // TODO: Decide
  // if (this->api_client.config.should_toggle_dynamic_trend_type &&
  //     !this->closed_positions.empty()) {
  //   const position_t last_position = this->closed_positions.back();
  //   const std::string original = this->api_client.config.dynamic_trend_type;

  //   if (last_position.close_order.min_profit <=
  //       last_position.close_order.stop_loss) {
  //     this->dynamic_trend_type = original;
  //   } else {
  //     const std::string opposite = original == "TRANS" ? "CIS" : "TRANS";
  //     this->dynamic_trend_type = opposite;
  //   }
  // }

  const double mid_percentile = day_range_percentile(current_mid());

  if (this->dynamic_trend_type == "CIS") {
    this->current_trend.trend =
        mid_percentile >= 50.0 ? trend_t::TREND_UP : trend_t::TREND_DOWN;

    return;
  }

  this->current_trend.trend =
      mid_percentile >= 50.0 ? trend_t::TREND_DOWN : trend_t::TREND_UP;
}

#endif
