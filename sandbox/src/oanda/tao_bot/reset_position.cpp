#ifndef OANDA__TAO_BOT_reset_position
#define OANDA__TAO_BOT_reset_position

/*
 * Oanda::TaoBot
 * exit_prices_t
 * order_status_t
 * position_t
 * reversal_t
 */
#include "tao_bot.h"

#include "build_performance.cpp"         // build_performance
#include "reset_orders.cpp"              // reset_orders
#include "should_toggle_is_trending.cpp" // should_toggle_is_trending
#include "toggle_is_trending.cpp"        // toggle_is_trending

void Oanda::TaoBot::reset_position() {
  if (!(this->close_order_ptr && this->open_order_ptr)) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED ||
      this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  // TODO: Decide
  if (this->api_client.config.should_await_spike) {
    this->current_trend.is_initialized = false;
  }

  if (should_toggle_is_trending(this->close_order, this->open_order)) {
    toggle_is_trending(this->close_order);
  }

  // TODO: Decide
  // if (this->close_order.profit < 0) {
  //   this->is_entry_signal_trans = !this->is_entry_signal_trans;
  // }

  const position_t position = {
      .close_order = this->close_order,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(position);
  this->entry_reversal = reversal_t();

  reset_orders();

  this->exit_prices = exit_prices_t();
  this->performance = build_performance();
}

#endif
