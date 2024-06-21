#ifndef ALPACA__TAO_BOT_reset_position
#define ALPACA__TAO_BOT_reset_position

/*
 * Alpaca::TaoBot
 * exit_prices_t
 * order_status_t
 * position_t
 * trend_meta_t
 */
#include "tao_bot.h"

#include "build_performance.cpp"         // build_performance
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

  // TODO: Decide
  if (should_toggle_is_trending(this->close_order, this->open_order)) {
    toggle_is_trending(this->close_order);
    // } else {
    //   this->current_trend = trend_meta_t();
  }

  // if (this->should_stop_profit) {
  //   trend_t new_trend = trend_t::TREND_CONSOLIDATION;

  //   if (this->close_order.profit > 0) {
  //     new_trend = this->close_order.action == order_action_t::BUY
  //                     ? trend_t::TREND_DOWN
  //                     : trend_t::TREND_UP;
  //   } else {
  //     new_trend = this->close_order.action == order_action_t::BUY
  //                     ? trend_t::TREND_UP
  //                     : trend_t::TREND_DOWN;
  //   }

  //   this->current_trend.at = this->current_epoch;
  //   this->current_trend.trend = new_trend;
  // } else if (should_toggle_is_trending(this->close_order)) {
  //   toggle_is_trending(this->close_order);
  // }

  const position_t position = {
      .close_order = this->close_order,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(position);
  this->entry_reversal = reversal_t();

  this->close_order_ptr = nullptr;
  this->exit_prices = exit_prices_t();
  this->open_order_ptr = nullptr;

  this->performance = build_performance();
}

#endif
