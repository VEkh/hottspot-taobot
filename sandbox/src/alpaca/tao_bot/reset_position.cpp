#ifndef ALPACA__TAO_BOT_reset_position
#define ALPACA__TAO_BOT_reset_position

/*
 * Alpaca::TaoBot
 * exit_prices_t
 * order_status_t
 * position_t
 * reversal_t
 */
#include "tao_bot.h"

#include "build_performance.cpp"            // build_performance
#include "has_just_reached_stop_profit.cpp" // has_just_reached_stop_profit // TODO: Decide
#include "reset_orders.cpp"                 // reset_orders
#include "should_toggle_is_trending.cpp" // should_toggle_is_trending
#include "toggle_is_trending.cpp"        // toggle_is_trending

void Alpaca::TaoBot::reset_position() {
  if (!(this->close_order_ptr && this->open_order_ptr)) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED ||
      this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  if (should_toggle_is_trending(this->close_order, this->open_order)) {
    toggle_is_trending(this->close_order);
  }

  const position_t position = {
      .close_order = this->close_order,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(position);
  this->entry_reversal = reversal_t();

  reset_orders();

  // TODO: Decide
  this->has_stopped_profit = has_just_reached_stop_profit();

  if (this->has_stopped_profit ||
      !this->api_client.config.should_reverse_at_trend_slip) {
    const position_t last_position = this->closed_positions.back();

    this->current_trend.at = last_position.close_order.timestamp;
    this->current_trend.trend =
        last_position.close_order.action == order_action_t::SELL
            ? trend_t::TREND_DOWN
            : trend_t::TREND_UP;
  }

  this->exit_prices = exit_prices_t();
  this->performance = build_performance();
}

#endif
