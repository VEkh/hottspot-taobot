#ifndef OANDA__TAO_BOT_should_toggle_is_trending
#define OANDA__TAO_BOT_should_toggle_is_trending

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::should_toggle_is_trending(order_t &close_order,
                                              order_t &open_order) {
  if (!this->open_order_ptr) {
    return false;
  }

  if (close_order.min_profit > close_order.stop_loss) {
    // TODO: Decide
    if (close_order.stop_profit_reversal.at) {
      this->current_trend.at = close_order.stop_profit_reversal.at;
      this->current_trend.trend =
          close_order.stop_profit_reversal.to_trend_type();
    } else {
      this->current_trend.at = close_order.timestamp;
      this->current_trend.trend = open_order.entry_reversal.to_trend_type();
    }

    return false;
  }

  // TODO: Decide
  if (this->api_client.config.should_stop_profit &&
      this->close_order.profit > 0) {
    this->current_trend.at = close_order.timestamp;
    this->current_trend.trend = open_order.entry_reversal.to_trend_type();

    return false;
  }

  // TODO: Decide
  if (!this->api_client.config.should_immediately_stop_loss) {
    this->current_trend.at = close_order.timestamp;
    this->current_trend.trend = open_order.entry_reversal.to_trend_type();

    return false;
  }

  return true;
}

#endif
