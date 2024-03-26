#ifndef ALPACA__TAO_BOT_reset_position
#define ALPACA__TAO_BOT_reset_position

/*
 * Alpaca::TaoBot
 * exit_prices_t
 * order_status_t
 * position_t
 * trend_meta_t
 * trend_t
 */
#include "tao_bot.h"

#include "build_performance.cpp"         // build_performance
#include "is_trending.cpp"               // is_trending // TODO: Decide
#include "should_toggle_is_trending.cpp" // should_toggle_is_trending // TODO: Decide

void Alpaca::TaoBot::reset_position() {
  if (!(this->close_order_ptr && this->open_order_ptr)) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED ||
      this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  if (this->close_order.profit < 0) {
    if (should_toggle_is_trending()) {
      double new_trend_at = 0;
      trend_t new_trend;

      if (is_trending()) {
        new_trend = trend_t::TREND_CONSOLIDATION;
      } else {
        new_trend = this->close_order.action == order_action_t::BUY
                        ? trend_t::TREND_UP
                        : trend_t::TREND_DOWN;
        new_trend_at = this->current_epoch;
      }

      this->current_trend = {
          .at = new_trend_at,
          .trend = new_trend,
      };
    }
  } else {
    this->current_trend = trend_meta_t();
  }

  const position_t position = {
      .close_order = this->close_order,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(position);
  this->entry_reversal = reversal_t();
  this->ref_reversal = reversal_t();

  this->close_order_ptr = nullptr;
  this->exit_prices = exit_prices_t();
  this->open_order_ptr = nullptr;

  this->performance = build_performance();
}

#endif
