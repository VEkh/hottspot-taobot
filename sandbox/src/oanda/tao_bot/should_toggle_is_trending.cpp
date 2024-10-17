#ifndef OANDA__TAO_BOT_should_toggle_is_trending
#define OANDA__TAO_BOT_should_toggle_is_trending

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::should_toggle_is_trending(order_t &close_order_,
                                              order_t &open_order_) {
  if (!this->open_order_ptr) {
    return false;
  }

  if (close_order_.min_profit > close_order_.stop_loss) {
    // TODO: Decide
    if (close_order_.stop_profit_reversal.at) {
      this->current_trend.at = close_order_.stop_profit_reversal.at;
      this->current_trend.trend =
          close_order_.stop_profit_reversal.to_trend_type();
    } else {
      this->current_trend.at = close_order_.timestamp;
      this->current_trend.trend = open_order_.entry_reversal.to_trend_type();
    }

    return false;
  }

  // TODO: Decide
  if (this->api_client.config.should_stop_profit && close_order_.profit > 0) {
    this->current_trend.at = close_order_.timestamp;
    this->current_trend.trend = open_order_.entry_reversal.to_trend_type();

    return false;
  }

  // TODO: Decide
  if (!this->api_client.config.should_immediately_stop_loss) {
    this->current_trend.at = close_order_.timestamp;
    this->current_trend.trend = open_order_.entry_reversal.to_trend_type();

    return false;
  }

  return true;
}

#endif
