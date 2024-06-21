#ifndef ALPACA__TAO_BOT_should_toggle_is_trending
#define ALPACA__TAO_BOT_should_toggle_is_trending

#include "is_non_init_reversing.cpp" // is_non_init_reversing // TODO: Decide
#include "is_trending.cpp"           // is_trending
#include "tao_bot.h"                 // Alpaca::TaoBot, position_t

bool Alpaca::TaoBot::should_toggle_is_trending(order_t &close_order,
                                               order_t &open_order) {
  if (!this->open_order_ptr) {
    return false;
  }

  const bool is_trending_ = is_trending();

  // TODO: Decide
  if (!this->api_client.config.reverse_profit_during.empty()) {
    if (this->api_client.config.should_await_after_no_max_loss) {
      if (close_order.min_profit > close_order.stop_loss) {
        this->current_trend.at = this->current_epoch;
        this->current_trend.trend = close_order.action == order_action_t::BUY
                                        ? trend_t::TREND_DOWN
                                        : trend_t::TREND_UP;

        return false;
      }

      // TODO: Decide
      // if (this->api_client.config
      //         .should_immediately_reverse_non_init_reversing) {
      //   // Only allow one immediate reversal
      //   if (!this->closed_positions.empty()) {
      //     const position_t last_position = this->closed_positions.back();

      //     if (!is_trending(last_position.open_order.trend)) {
      //       return true;
      //     }
      //   }

      //   return !is_non_init_reversing(this->open_order_ptr);
      // }

      return true;
    } else {
      if (close_order.min_profit > close_order.stop_loss) {
        this->current_trend.at = close_order.stop_profit_reversal.at;
        this->current_trend.trend =
            close_order.stop_profit_reversal.to_trend_type();

        return false;
      }

      // TODO: Decide
      // if (this->api_client.config
      //         .should_immediately_reverse_non_init_reversing) {
      //   if (!this->closed_positions.empty()) {
      //     const position_t last_position = this->closed_positions.back();

      //     if (!is_trending(last_position.open_order.trend)) {
      //       return true;
      //     }
      //   }

      //   return !is_non_init_reversing(this->open_order_ptr);
      // }

      return true;
    }
  }

  if (this->should_stop_profit) {
    // TODO: Decide
    // if (close_order.min_profit > close_order.stop_loss) {
    //   return false;
    // }

    if (close_order.profit > 0) {
      this->current_trend.at = this->current_epoch;

      return !is_trending_;
    }

    return true;
  }

  return true;
}

#endif
