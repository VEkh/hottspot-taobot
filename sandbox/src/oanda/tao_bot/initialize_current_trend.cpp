// TODO: Decide
#ifndef OANDA__TAO_BOT_initialize_current_trend
#define OANDA__TAO_BOT_initialize_current_trend

#include "force_init_reversal_await.cpp" // force_init_reversal_await
#include "tao_bot.h" // Oanda::TaoBot, order_action_t, position_t, trend_t

void Oanda::TaoBot::initialize_current_trend() {
  if (this->api_client.config.should_enter_at_spike) {
    return;
  }

  if (this->closed_positions.empty()) {
    force_init_reversal_await();

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
