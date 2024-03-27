#ifndef ALPACA__TAO_BOT_toggle_is_trending
#define ALPACA__TAO_BOT_toggle_is_trending

#include "is_trending.cpp" // is_trending
#include "tao_bot.h"       // Alpaca::TaoBot, trend_t

void Alpaca::TaoBot::toggle_is_trending(const order_t &order) {
  double new_trend_at = 0;
  trend_t new_trend;

  if (is_trending()) {
    new_trend = trend_t::TREND_CONSOLIDATION;
  } else {
    new_trend = order.action == order_action_t::BUY ? trend_t::TREND_UP
                                                    : trend_t::TREND_DOWN;
    new_trend_at = this->current_epoch;
  }

  this->current_trend = {
      .at = new_trend_at,
      .trend = new_trend,
  };
}

#endif
