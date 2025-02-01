#ifndef ALPACA__TAO_BOT_should_toggle_is_trending
#define ALPACA__TAO_BOT_should_toggle_is_trending

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::should_toggle_is_trending(order_t &close_order,
                                               order_t &open_order) {
  // TODO: Decide
  if (this->api_client.config.should_enter_at_spike) {
    return false;
  }

  if (!this->open_order_ptr) {
    return false;
  }

  // TODO: Decide
  if (this->api_client.config.should_stop_profit && open_order.stop_profit &&
      open_order.max_profit >= open_order.stop_profit) {
    this->current_trend.at = close_order.timestamp;
    this->current_trend.trend = open_order.entry_reversal.to_trend_type();

    return false;
  }

  if (close_order.min_profit > close_order.stop_loss) {
    this->current_trend.at = close_order.stop_profit_reversal.at;
    this->current_trend.trend =
        close_order.stop_profit_reversal.to_trend_type();

    return false;
  }

  return true;
}

#endif
