#ifndef ALPACA__TAO_BOT_initialize_current_trend
#define ALPACA__TAO_BOT_initialize_current_trend

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, trend_t

void Alpaca::TaoBot::initialize_current_trend() {
  if (this->closed_positions.empty()) {
    return;
  }

  const position_t last_position = this->closed_positions.back();

  if (last_position.close_order.profit > 0) {
    return;
  }

  this->current_trend.at = last_position.close_order.timestamp;
  this->current_trend.trend =
      last_position.close_order.action == order_action_t::SELL
          ? trend_t::TREND_DOWN
          : trend_t::TREND_UP;
}

#endif
